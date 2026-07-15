/*
 * LedPwm.c
 *
 *  Created on: 12 de jul. de 2026
 *      Author: quesia
 */

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/
#include "LedPwm.h"
#include "Bsp.h"

/*******************************************************************************
 * VARIÁVEIS LOCAIS
 ******************************************************************************/
static uint8_t ledSelecionado;

static uint8_t dutyLed1; //intensidade do led
static uint8_t dutyLed2;
static uint8_t dutyLed3;

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/
/******************************************************************************
 * @brief Inicializa o módulo LedPwm.
 * @param nenhum.
 * @retval nenhum.
 ******************************************************************************/
void LedPwm_Init(void)
{
    ledSelecionado = 1;
    dutyLed1 = 0;
    dutyLed2 = 0;
    dutyLed3 = 0;
    Bsp_Set_LED1(0);
    Bsp_Set_LED2(0);
    Bsp_Set_LED3(0);
}

/******************************************************************************
 * @brief Seleciona o LED ativo.
 * @param qual LED será ustilizado, 1,2 ou 3..
 * @retval nenhum.
 ******************************************************************************/
void LedPwm_SelectLed(uint8_t led)
{
    if((led >= 1) && (led <= 3))
    {
        ledSelecionado = led;
    }
}

/******************************************************************************
 * @brief Atualiza o brilho do LED selecionado.
 * @param percent Intensidade em porcentagem.
 * @retval nenhum.
 ******************************************************************************/
void LedPwm_Update(uint8_t percent)
{
    switch(ledSelecionado)
    {
        case 1:
            dutyLed1 = percent;
            Bsp_Set_LED1(dutyLed1);
            break;

        case 2:
            dutyLed2 = percent;
            Bsp_Set_LED2(dutyLed2);
            break;

        case 3:
            dutyLed3 = percent;
            Bsp_Set_LED3(dutyLed3);
            break;

        default:
            break;
    }
}

/******************************************************************************
 * @brief Retorna o LED selecionado.
 * @param nenhum.
 * @retval LED ativo.
 ******************************************************************************/
uint8_t LedPwm_GetSelected(void)
{
    return ledSelecionado;
}
