/*
 * Button.c
 *
 *  Created on: 13 de jul. de 2026
 *      Author: quesia
 */

#include "Button.h"
#include "Bsp.h"

/*******************************************************************************
 * VARIÁVEIS LOCAIS
 ******************************************************************************/

static uint8_t freeze;

static uint8_t debounce;

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/

/******************************************************************************
 * @brief Inicializa o módulo Button.
 * @param nenhum.
 * @retval nenhum.
 ******************************************************************************/
void Button_Init(void)
{
    freeze = 0;
    debounce = 0;
}

/******************************************************************************
 * @brief processa o botão utilizando debounce por timer dedicado
 * @param nenhum.
 * @retval nenhum.
 ******************************************************************************/
void Button_Debounce(void)
{
    // se o botão foi pressionado
    if(Bsp_Get_ButtonFlag())
    {
        Bsp_Clear_ButtonFlag();
        debounce = 1;
    }

    // fim do debounce
    if(debounce && Bsp_Get_DebounceFlag())
    {
        Bsp_Clear_DebounceFlag();
        debounce = 0;
        freeze = !freeze; //muda o estado
    }
}
