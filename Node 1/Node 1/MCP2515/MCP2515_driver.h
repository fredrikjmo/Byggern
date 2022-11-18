/*
 * MCP2515_driver.h
 *
 * Created: 05.10.2022 09:43:22
 *  Author: fjmo
 */ 
#include "../MCP2515/MCP2515_constants.h"
#include "../SPI/SPI_driver.h"
#include <avr/io.h>

#ifndef MCP2515_DRIVER_H_
#define MCP2515_DRIVER_H_

uint8_t MCP2515_init(void);

uint8_t MCP2515_read(uint8_t address);

uint8_t MCP2515_set_mode(uint8_t mode);

void MCP2515_write(uint8_t address, uint8_t data);

void MCP2515_request_to_send(uint8_t MCP_RTS_N);

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

void MCP2515_reset(void);

uint8_t MCP2515_read_status(void);

#endif /* MCP2515_DRIVER_H_ */