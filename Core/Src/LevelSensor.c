/*
 * LevelSensor.c
 *
 *  Created on: 3 de jul. de 2026
 *      Author: Quesia
 */

#include "LevelSensor.h"

#define NUM_SAMPLES 20

static uint32_t soma = 0;
static uint8_t contador = 0;
static float tensao = 0;
static uint8_t percentual = 0;

void LevelSensor_NewSample(uint32_t sample)
{
    soma += sample;
    contador++;
}

bool LevelSensor_IsReady(void)
{
    return (contador >= NUM_SAMPLES);
}

float LevelSensor_GetVoltage(void)
{
    uint32_t media = soma / NUM_SAMPLES;
    tensao = (media * 3.3f) / 4095.0f;
    return tensao;
}

uint8_t LevelSensor_GetPercent(void)
{
    uint32_t media = soma / NUM_SAMPLES;
    percentual = (media * 100) / 4095;
    return percentual;
}

void LevelSensor_Reset(void)
{
    soma = 0;
    contador = 0;
}
