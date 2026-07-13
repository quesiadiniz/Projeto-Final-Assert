/*
 * Sampler.h
 *
 *  Created on: 11 de jul. de 2026
 *      Author: quesia
 */

#ifndef INC_SAMPLER_H_
#define INC_SAMPLER_H_

/***********************************************************************************************************************
 * INCLUDES NECESSARIOS
 **********************************************************************************************************************/
#include "stdint.h"

/***********************************************************************************************************************
 * PROTOTIPOS PUBLICOS
 **********************************************************************************************************************/
void Sampler_Init(void);
void Sampler_AddSample(uint16_t sample);

uint8_t Sampler_IsReady(void);
uint8_t Sampler_GetPercent(void);

void Sampler_ClearReady(void);

#endif /* INC_SAMPLER_H_ */
