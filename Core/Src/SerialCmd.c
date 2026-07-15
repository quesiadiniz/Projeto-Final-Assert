/*
 * SerialCmd.c
 *
 *  Created on: 12 de jul. de 2026
 *      Author: quesia
 */

/*******************************************************************************
 * INCLUDES NECESSARIOS
 ******************************************************************************/
#include "SerialCmd.h"
#include "LedPwm.h"
#include <string.h>

/*******************************************************************************
 * DEFINES
 ******************************************************************************/
#define SIZE_COMAND 5 //tamanho maximo que uma instrução pode ter (ledx\0)

/*******************************************************************************
 * VARIÁVEIS LOCAIS
 ******************************************************************************/
static char cmd[SIZE_COMAND];
static uint8_t indice;

/*******************************************************************************
 * FUNÇÕES PÚBLICAS
 ******************************************************************************/

/******************************************************************************
 * @brief Inicializa o módulo SerialCmd.
 * @param nenhum.
 * @retval nenhum.
 ******************************************************************************/
void SerialCmd_Init(void)
{
    indice = 0;
    memset(&cmd[0], 0, sizeof(cmd)); //escreve 0 em todas as posições do array cmd, limpra completamente o buffr para receber o proc comando
}

/******************************************************************************
 * @brief Processa um caractere recebido da USART.
 * @param rxByte Caractere recebido.
 * @retval nenhum.
 ******************************************************************************/
void SerialCmd_ProcessChar(uint8_t rxByte)
{
    if(indice < (SIZE_COMAND - 1)) // -1 por cauda do \0
    {
        cmd[indice++] = rxByte;
    }

    if(indice == 4) // index = 4 é quando se recebeu todos os caracteres
    {
        cmd[4] = '\0';

        if(strcmp(cmd, "LED1") == 0)
        {
            LedPwm_SelectLed(1);
        }
        else if(strcmp(cmd, "LED2") == 0)
        {
            LedPwm_SelectLed(2);
        }
        else if(strcmp(cmd, "LED3") == 0)
        {
            LedPwm_SelectLed(3);
        }

        indice = 0;
        memset(&cmd[0], 0, sizeof(cmd));
    }
}

