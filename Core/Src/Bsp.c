/*
 * Bsp.c
 *
 *  Created on: 11 de jul. de 2026
 *      Author: quesia
 */


/***********************************************************************************************************************
 * INCLUDES NECESSARIOS
 **********************************************************************************************************************/
#include "Bsp.h"
#include <string.h>

/*******************************************************************************
 * VARIÁVEIS EXTERNAS (CubeMX)
 ******************************************************************************/
extern ADC_HandleTypeDef hadc1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart3;

/*******************************************************************************
 * VARIÁVEIS LOCAIS
 ******************************************************************************/
static volatile uint8_t adcFlag = 0;
static volatile uint8_t debounceFlag = 0;
static volatile uint8_t buttonFlag = 0;

static uint8_t rxByte;

/*******************************************************************************
 * PROTÓTIPOS LOCAIS
 ******************************************************************************/
static void PWM_Init(void);
static uint32_t PWM_PercentToCompare(uint8_t percent);

/*******************************************************************************
 FUNCOES PUBLICAS
*******************************************************************************/

/******************************************************************************/
/** @brief inicia todas as configurações necessarias do BSP
 * * @param nenhum
 * * @retval nenhum.
******************************************************************************/
void Bsp_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim2); //amostragem
	HAL_TIM_Base_Start_IT(&htim4); //debounce
	PWM_Init();
	HAL_UART_Receive_IT(&huart3, &rxByte, 1);
}
/******************************************************************************/
/** @brief inicia todos os canais de pwm para os leds
 * * @param nenhum
 * * @retval nenhum.
 * ******************************************************************************/
static void PWM_Init()
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

/******************************************************************************/
 /* @brief Lê o ADC.
 * @param Nenhum.
 * @retval Valor do ADC.
******************************************************************************/
uint16_t Bsp_ADC_Read(void)
{
    HAL_ADC_Start(&hadc1);

    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint16_t value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return value;
}

/******************************************************************************/
/** @brief atualiza o PWM dos LED1, 2 e 3
 * * @param nenhum
 * * @retval nenhum.
 * ******************************************************************************/
void Bsp_Set_LED1(uint8_t porcentagem)
{
	uint32_t compare = (porcentagem * (__HAL_TIM_GET_AUTORELOAD(&htim3) + 1)) / 100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, compare);
}

void Bsp_Set_LED2(uint8_t porcentagem)
{
	uint32_t compare = (porcentagem * (__HAL_TIM_GET_AUTORELOAD(&htim3) + 1)) / 100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, compare);
}

void Bsp_Set_LED3(uint8_t porcentagem)
{
	uint32_t compare = (porcentagem * (__HAL_TIM_GET_AUTORELOAD(&htim3) + 1)) / 100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, compare);
}

/******************************************************************************/
/** @brief a USART recebe do usuario qual led será acionado, e guarda no rxByte
 * * @param nenhum
 * * @retval nenhum.
 * ******************************************************************************/
void Bsp_Usart3_Transmit(char *led)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)led, strlen(led), HAL_MAX_DELAY);
}

/******************************************************************************/
/** @brief habilita uma nova recepçao da usart
********************************************************************************/
void Bsp_Usart3_Receive_IT(void)
{
	HAL_UART_Receive_IT(&huart3, &rxByte, 1);
}


/******************************************************************************/
/** @brief Retorna o último byte recebido.
********************************************************************************/
uint8_t Bsp_Get_RxByte(void)
{
    return rxByte;
}

/******************************************************************************/
/** @brief atualiza/retorna as flags do ADC e do Debounce
 * * @param nenhum
 * * @retval nenhum.
 * ******************************************************************************/
uint8_t Bsp_Get_ADCFlag(void)
{
    return adcFlag;
}

void Bsp_Clear_ADCFlag()
{
	adcFlag = 0;
}

uint8_t Bsp_Get_DebounceFlag(void)
{
    return debounceFlag;
}

void Bsp_Clear_DebounceFlag()
{
	debounceFlag = 0;
}

uint8_t Bsp_Get_ButtonFlag(void)
{
    return buttonFlag;
}

void Bsp_Clear_ButtonFlag(void)
{
	buttonFlag = 0;
}

/*******************************************************************************
 * CALLBACKS HAL
 ******************************************************************************/

/*******************************************************************************
 * @brief Callback dos timers.
 * * @param timer utilizado (*htimx)
 * * @retval nenhum.
 ******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        adcFlag = 1;
    }

    if (htim->Instance == TIM4)
    {
        debounceFlag = 1;
    }
}

/******************************************************************************
 * @brief Callback do botão.
 * * @param pino utilizado
 * * @retval nenhum.
 ******************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    buttonFlag = 1;
}

/******************************************************************************
 * @brief Callback da USART3
 * * @param huartx
 * * @retval nenhum.
 ******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        Bsp_Usart3_Receive_IT();
    }
}





























