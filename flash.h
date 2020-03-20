#ifndef FLASH_H
#define FLASH_H


#include "stm32f4xx_hal.h"         
#define CS_H HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
#define CS_L HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);

void read_data(uint32_t address,uint8_t* data,uint16_t size);
uint8_t read_status_register(void);
void write_status_register(uint8_t data);
void write_array(uint32_t address,uint8_t* data,uint16_t size);
void clear(void);

#endif
