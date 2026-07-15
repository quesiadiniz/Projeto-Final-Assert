/*
 * LedPwm.h
 *
 *  Created on: 12 de jul. de 2026
 *      Author: quesia
 */

#ifndef INC_LEDPWM_H_
#define INC_LEDPWM_H_

/*******************************************************************************
 * INCLUDES NECESSÁRIOS
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * PROTÓTIPOS PÚBLICOS
 ******************************************************************************/
void LedPwm_Init(void);
void LedPwm_SelectLed(uint8_t led);
void LedPwm_Update(uint8_t percent);

uint8_t LedPwm_GetSelected(void);

#endif /* INC_LEDPWM_H_ */
