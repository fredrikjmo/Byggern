/*
 * xmem.c
 *
 * Created: 15.09.2022 08:59:14
 *  Author: fjmo
 */ 

#include "xmem.h"

uint8_t m_max_x_value = 0;
uint8_t m_min_x_value = 255;
uint8_t m_middle_x_value = 0;

uint8_t m_max_y_value = 0;
uint8_t m_min_y_value = 255;
uint8_t m_middle_y_value = 0;

pos_p posistion_percentage;


void xmem_init ( void ){
	MCUCR |= (1 << SRE ); // enable XMEM
	SFIOR |= (1 << XMM2 ); // mask unused bits
}
void adc_init ( void ){

	DDRD |= (1<<DDD5); // Set Data Direction PD5 to Write (output)
	DDRD |= (0<<DDD4); // Set Data Direction PD4 to Read (input). Used for BUSY from ADC
	
	TCCR1B |= (1<<WGM12 | 0<<WGM13); // Set CTC mode
	TCCR1A |= (0<<WGM10 | 0<<WGM11); // Set CTC mode
	
	TCCR1B |= (1<<CS10 | 0<<CS11 | 0<<CS12); //Clk frequency equal to system clock

	TCCR1A |= (0<<COM1A1 | 1<<COM1A0); // Set 0C1A to toggle on match
	
	OCR1A = 0x0; // Set compare to 0. Timer reset on compare equal, will always stay at 0, toggle every cycle (?)

}

void adc_sample( void ){
	
	volatile char * ext_mem = ( char *) 0x1400;
	ext_mem [ 0 ] = 0x01;
}

uint8_t adc_read ( uint8_t channel ){
	
	adc_sample();
	
	while((PIND & 1<<PIND4) == 0 ){}// While BUSY is low, spin here

	//_delay_ms(100);
	volatile char * ext_mem = ( char *) 0x1400 ;
	uint8_t ch_0 = ext_mem [ 0 ];
	uint8_t ch_1 = ext_mem [ 0 ];
	uint8_t ch_2 = ext_mem [ 0 ];
	uint8_t ch_3 = ext_mem [ 0 ];
	
	switch (channel)
	{
		case 0:
			return ch_0;
		
		case 1:
			return ch_1;

		case 2:
			return ch_2;

		case 3:
			return ch_3;

		default:
			return 0;
	}
}

void adc_calibrate( void ){
	uint8_t adc_x = adc_read(0);
	uint8_t adc_y = adc_read(1);
	
	if(m_middle_x_value == 0)
		m_middle_x_value = adc_x;
	
	if(m_middle_y_value == 0)
		m_middle_y_value = adc_y;
	
	//setting max and min values for x-values of joystick
	if (adc_x > m_max_x_value)
		m_max_x_value = adc_x;

	if (adc_x < m_min_x_value)
		m_min_x_value = adc_x;

	//setting max and min values for y-values of joystick
	if (adc_y > m_max_y_value)
		m_max_y_value = adc_y;
	
	if (adc_y < m_min_y_value)
		m_min_y_value = adc_y;
}

void xmem_write ( uint8_t data , uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	ext_mem [ addr ]= data ;
}
uint8_t xmem_read ( uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
}

pos_p pos_read(void){
	
	int16_t adc_x = adc_read(0);
	int16_t adc_y = adc_read(1);

	if(adc_x <= m_middle_x_value)
		posistion_percentage.x_axis	= 100*(adc_x - m_middle_x_value)/(m_middle_x_value-m_min_x_value);
	else
		posistion_percentage.x_axis	= 100*(adc_x - m_middle_x_value)/(m_max_x_value-m_middle_x_value);

	if(adc_y <= m_middle_y_value)
		posistion_percentage.y_axis	= 100*(adc_y - m_middle_y_value)/(m_middle_y_value-m_min_y_value);
	else
		posistion_percentage.y_axis	= 100*(adc_y - m_middle_y_value)/(m_max_y_value-m_middle_y_value);
	
	return posistion_percentage;
}

direction direction_read (void){
	if((posistion_percentage.x_axis < 5)&&(posistion_percentage.x_axis > -5)&&(posistion_percentage.y_axis < 5)&&(posistion_percentage.x_axis > -5))
		return neutral;

	if(abs(posistion_percentage.x_axis) <= abs(posistion_percentage.y_axis)){
		if(posistion_percentage.y_axis < 0)
			return down;
		return up;}
	else{
		if(posistion_percentage.x_axis < 0)
			return left;
		return right;}
} 

uint8_t pos_left_slider(void){	uint8_t L_slider = adc_read(2);	return 100*L_slider/255;}uint8_t pos_right_slider(void){

	uint8_t R_slider = adc_read(3);
	return 100*R_slider/255;
}

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\r\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\r\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\r\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \r\n%4d errors in write phase and \r\n%4d errors in retrieval phase\r\n\r\n", write_errors, retrieval_errors);
}
