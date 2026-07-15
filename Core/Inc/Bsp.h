/*
 * Bsp.h
 *
 *  Created on: 11 de jul. de 2026
 *      Author: quesia
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

/***********************************************************************************************************************
 * INCLUDES NECESSARIOS
 **********************************************************************************************************************/
#include "main.h"
#include <stdint.h>

/***********************************************************************************************************************
 * PROTOTIPOS PUBLICOS
 **********************************************************************************************************************/
void Bsp_Init(void); //inicialização

void Bsp_Set_LED1(uint8_t percent); //leds com pwm
void Bsp_Set_LED2(uint8_t percent);
void Bsp_Set_LED3(uint8_t percent);

void Bsp_UartTransmit(char *msg);
void Bsp_UartReceiveIT(void);
uint8_t Bsp_Get_RxByte(void);

uint16_t Bsp_ADC_Read(void); // ADC

uint8_t Bsp_Get_ADCFlag(void); //flag
void Bsp_Clear_ADCFlag(void);

uint8_t Bsp_Get_DebounceFlag(void); //flag
void Bsp_Clear_DebounceFlag(void);

uint8_t Bsp_Get_ButtonFlag(void); //flag
void Bsp_Clear_ButtonFlag(void);



#endif /* INC_BSP_H_ */
