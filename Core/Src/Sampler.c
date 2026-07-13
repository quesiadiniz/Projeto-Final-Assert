/*
 * Sampler.c
 *
 *  Created on: 11 de jul. de 2026
 *      Author: quesia
 */

#include "Sampler.h"

#define SAMPLE_NUMBER      100 //numero de amostras
#define ADC_MAX_VALUE      4095 //numero max dos passos do adc em 12bits

/******************************************************************************
 * Variáveis locais
 ******************************************************************************/

static uint32_t sumSamples;
static uint16_t sampleCounter;

static uint8_t percentValue;
static uint8_t readyFlag;

/*******************************************************************************
 FUNCOES PUBLICAS
*******************************************************************************/
/******************************************************************************
 * @brief Inicializa as variáveis do módulo Sampler.
 * @param nenhum.
 * @retval nenhum.
******************************************************************************/
void Sampler_Init(void)
{
    sumSamples = 0;
    sampleCounter = 0;
    percentValue = 0;
    readyFlag = 0;
}

/******************************************************************************
 * @brief Adiciona uma nova amostra do ADC ao acumulador.
 * @param sample Valor lido do conversor ADC.
 * @retval nenhum.
******************************************************************************/
void Sampler_AddSample(uint16_t sample)
{
    sumSamples += sample;
    sampleCounter++;

    if(sampleCounter >= SAMPLE_NUMBER)
    {
        uint32_t media;

        // calcula a media das 100 amostras
        media = sumSamples / SAMPLE_NUMBER;

        // converte para porcentagem (0 a 100%)
        percentValue = (media * 100) / ADC_MAX_VALUE;

        //Indica que há um novo valor disponível
        readyFlag = 1;

        // Reinicia a aquisição
        sumSamples = 0;
        sampleCounter = 0;
    }
}

/******************************************************************************
 * @brief Verifica se uma nova média das amostras está disponível.
 * @param nenhum.
 * @retval 1 caso exista uma nova média disponível, 0 caso contrário.
******************************************************************************/
uint8_t Sampler_IsReady(void)
{
    return readyFlag;
}

/******************************************************************************
 * @brief Retorna o valor médio convertido para porcentagem (0 a 100%).
 * @param nenhum.
 * @retval Valor da média em porcentagem.
******************************************************************************/
uint8_t Sampler_GetPercent(void)
{
    return percentValue;
}

/******************************************************************************
 * @brief Limpa a flag que indica uma nova média disponível.
 * @param nenhum.
 * @retval nenhum.
******************************************************************************/
void Sampler_ClearReady(void)
{
    readyFlag = 0;
}



