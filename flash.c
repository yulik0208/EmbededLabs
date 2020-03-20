#include "flash.h"

extern SPI_HandleTypeDef hspi1;

void read_data(uint32_t address,uint8_t* data,uint16_t size){
	
	CS_L
	uint8_t _data[4];
	_data[0]=0x03;
	_data[1]=(address>>16)&0xFF;
	_data[2]=(address>>8)&0xFF;
	_data[3]=(address)&0xFF;
	HAL_SPI_Transmit(&hspi1,_data,4,0xFFFF);
	HAL_SPI_Receive(&hspi1,data,size,0xFFFF);
	CS_H
	
}

uint8_t read_status_register(){
	
	CS_L
	uint8_t _data=0x05;
	uint8_t status;
	HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
	HAL_SPI_Receive(&hspi1,&status,1,0xFFFF);
	CS_H
	
	return status;
	
}

void write_status_register(uint8_t data){
	
	CS_L
	
	uint8_t _data=0x50;
	
	HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
	CS_H
	CS_L
	
	_data = 0x01;
	
	HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
	HAL_SPI_Transmit(&hspi1,&data,1,0xFFFF);
	
	CS_H
	
}

void write_array(uint32_t address,uint8_t* data,uint16_t size){
  CS_L
  uint8_t _data[6];
  _data[0]=0x06;
  HAL_SPI_Transmit(&hspi1,_data,1,0xFFFF);
  CS_H
  CS_L
  _data[0] = 0xAD;
  _data[1] = (address>>16)&0xFF;
  _data[2] = (address>>8)&0xFF;
  _data[3] = (address)&0xFF;
  _data[4] = data[0];
  _data[5] = data[1];
  HAL_SPI_Transmit(&hspi1,_data,6,0xFFFF);
  CS_H
  for(uint8_t i=0;i<size/2;i++){
    CS_L
    _data[1] = data[i*2];
		_data[2] = data[i*2+1];
    HAL_SPI_Transmit(&hspi1,_data,3,0xFFFF);
    CS_H
    while((read_status_register()&0x01)==0x01);
  }
  CS_L
  _data[0]=0x04;
  HAL_SPI_Transmit(&hspi1,_data,1,0xFFFF);
  CS_H
}


void clear(){
  CS_L
  uint8_t _data=0x06;
  HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
  CS_H
  CS_L
  _data = 0x60;
  HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
  CS_H
}

