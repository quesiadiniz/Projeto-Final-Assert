/*
 * LevelSensor.h
 *
 *  Created on: 3 de jul. de 2026
 *      Author: Quesia
 */

#ifndef INC_LEVELSENSOR_H_
#define INC_LEVELSENSOR_H_

#include <stdint.h>
#include <stdbool.h>

void LevelSensor_NewSample(uint32_t sample);

bool LevelSensor_IsReady(void);

uint8_t LevelSensor_GetPercent(void);

float LevelSensor_GetVoltage(void);

void LevelSensor_Reset(void);

#endif

#endif /* INC_LEVELSENSOR_H_ */
