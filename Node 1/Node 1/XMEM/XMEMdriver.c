/*
 * xmem.c
 *
 * Created: 15.09.2022 08:59:14
 *  Author: fjmo
 */ 

#include "XMEMdriver.h"

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

void xmem_write ( uint8_t data , uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	ext_mem [ addr ]= data ;
}
uint8_t xmem_read ( uint16_t addr ){
	volatile char * ext_mem = ( char *) BASE_ADDRESS ;
	uint8_t ret_val = ext_mem [ addr ];
	return ret_val ;
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
