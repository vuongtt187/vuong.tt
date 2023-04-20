  /*
  * This file is part of the µOS++ distribution.
  *   (https://github.com/micro-os-plus)
  * Copyright (c) 2014 Liviu Ionescu.
  *
  * Permission is hereby granted, free of charge, to any person
  * obt/*
  * This file is part of the µOS++ distribution.
  *   (https://github.com/micro-os-plus)
  * Copyright (c) 2014 Liviu Ionescu.
  *
  * Permission is hereby granted, free of charge, to any person
  * obtaining a copy of this software and associated documentation
  * files (the "Software"), to deal in the Software without
  * restriction, including without limitation the rights to use,
  * copy, modify, merge, publish, distribute, sublicense, and/or
  * sell copies of the Software, and to permit persons to whom
  * the Software is furnished to do so, subject to the following
  * conditions:
  *
  * The above copyright notice and this permission notice shall be
  * included in all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  * OTHER DEALINGS IN THE SOFTWARE.
  */

  // ----------------------------------------------------------------------------

  #include <stdio.h>
  #include <stdlib.h>
  #include "diag/trace.h"

  #include <CLCD.h>
  #include <stdio.h>
  #include <String.h>
  #include <stm32f1xx_hal_gpio.h>
  #include <stm32f1xx_hal_tim.h>
  #include <stm32f1xx_hal.h>
  #include <stm32f1xx_hal_def.h>
  #include <stm32f1xx_hal_adc.h>
  #include <stm32f1xx_hal_adc_ex.h>


  /* USER CODE BEGIN Header */
  /* USER CODE END Header */
  /* Includes ------------------------------------------------------------------*/


  /* Private includes ----------------------------------------------------------*/
  /* USER CODE BEGIN Includes */
  /* USER CODE END Includes */

  /* Private typedef -----------------------------------------------------------*/
  /* USER CODE BEGIN PTD */
  /* USER CODE END PTD */

  /* Private define ------------------------------------------------------------*/
  /* USER CODE BEGIN PD */
  #define D4_Pin GPIO_PIN_4
  #define D4_GPIO_Port GPIOB
  #define D5_Pin GPIO_PIN_5
  #define D5_GPIO_Port GPIOB
  #define D6_Pin GPIO_PIN_6
  #define D6_GPIO_Port GPIOB
  #define D7_Pin GPIO_PIN_7
  #define D7_GPIO_Port GPIOB
  #define EN_Pin GPIO_PIN_3
  #define EN_GPIO_Port GPIOA
  #define CS_Pin GPIO_PIN_4
  #define CS_GPIO_Port GPIOA

  /* USER CODE END PD */

  /* Private macro -------------------------------------------------------------*/
  /* USER CODE BEGIN PM */
  /* USER CODE END PM */

  /* Private variables ---------------------------------------------------------*/

  /* USER CODE BEGIN PV */

  ADC_HandleTypeDef hadc1;
  TIM_HandleTypeDef htim1;
  /* USER CODE END PV */

  /* Private function prototypes -----------------------------------------------*/



  /* USER CODE END PFP */

  /* Private user code ---------------------------------------------------------*/
  /* USER CODE BEGIN 0 */
  CLCD_Name LCD1;

  uint8_t Count;
  char LCD_send[16];

  void SystemClock_Config(void)
  {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;


    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;


    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;

  }

  /**
    * @brief ADC1 Initialization Function
    * @param None
    * @retval None
    */
  static void MX_ADC1_Init(void)
  {

    /* USER CODE BEGIN ADC1_Init 0 */

    /* USER CODE END ADC1_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC1_Init 1 */

    /* USER CODE END ADC1_Init 1 */

    /** Common config
    */
    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;


    /** Configure Regular Channel
    */
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;


  }
  static void MX_GPIO_Init(void)
  {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

    /*Configure GPIO pins : PA3 PA4 */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PB4 PB5 PB6 PB7 */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
  }

  /* USER CODE BEGIN 4 */

  /* USER CODE END 4 */

  int main(void)
  {
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    MX_ADC1_Init();

    /* USER CODE BEGIN Init */
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
        MX_GPIO_Init();
    /* USER CODE BEGIN 2 */
    CLCD_4BIT_Init(&LCD1, 16, 2, CS_GPIO_Port, CS_Pin, EN_GPIO_Port, EN_Pin,
                    D4_GPIO_Port, D4_Pin, D5_GPIO_Port, D5_Pin,
                    D6_GPIO_Port, D6_Pin, D7_GPIO_Port, D7_Pin);

    /* USER CODE END 2 */
    uint32_t val = 0;
    char st[16] = "";
    /* Infinite loop */
    while(1) {
    /* USER CODE BEGIN WHILE */
      /* USER CODE END WHILE */


      HAL_ADC_Start(&hadc1);

      // Đợi cho chuyển đổi ADC1 hoàn thành
      if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
      {
        // Đọc giá trị ADC1
        val = HAL_ADC_GetValue(&hadc1);
      }

    // Dừng chuyển đổi ADC1
      HAL_ADC_Stop(&hadc1);

      sprintf(st, "tem: %d", val);

      CLCD_SetCursor(&LCD1,0,0);
      CLCD_WriteString(&LCD1, st);
      HAL_Delay(1000);
      /* USER CODE BEGIN 3 */
    /* USER CODE END 3 */
    }
  }
