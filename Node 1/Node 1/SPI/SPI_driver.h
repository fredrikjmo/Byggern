/*
 * SPI_driver.h
 *
 * Created: 05.10.2022 09:25:22
 *  Author: fjmo
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
#include <avr/io.h>

void SPI_MasterInit(void);

void SPI_write(uint8_t data);

uint8_t SPI_read(void);

#endif /* SPI_DRIVER_H_ */