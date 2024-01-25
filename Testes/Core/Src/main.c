/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* ************************************************************************************ */
/* * Includes                                                                         * */
/* ************************************************************************************ */
/* CeNTI library. */
#include "../../Project/CeNTI_Library/lib/CeNTI_lib_includes.h"

/* Project defines. */
#include "../../Project/Defines/Project_defines.h"

/* Manager library. */
#include "../../Project/Manager/Manager.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* ************************************************************************************ */
/* * Safety check                                                                     * */
/* ************************************************************************************ */
#if ((!(defined(CENTI_ENABLE))) || \
     (!(defined(CENTI_DISABLE))))

    #error CENTI_ENABLE and/or CENTI_DISABLE not defined! Define the in Project/CeNTI/Defines/CeNTI_defines.h file!

#endif

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* ************************************************************************************ */
/* * Flags                                                                            * */
/* ************************************************************************************ */
/* Used for software reset. */
volatile t_FLAG f_soft_reset = FLAG_OFF;

/* ************************************************************************************ */
/* * Enumerations                                                                     * */
/* ************************************************************************************ */
/* Main states. */
typedef enum _enum_MAIN_states {
    MAIN_STATE_INIT_ERROR = 0   ,
    MAIN_STATE_INIT             ,
    MAIN_STATE_LOOP_ERROR       ,
    MAIN_STATE_LOOP             ,
    /* Add more states. */
    /* ... */
}et_MAIN_STATE;

/* ************************************************************************************ */
/* * Global Variables                                                                 * */
/* ************************************************************************************ */
/* Main state. */
static et_MAIN_STATE g_et_state = MAIN_STATE_INIT;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* ************************************************************************************ */
/* * Main Functions Prototypes                                                        * */
/* ************************************************************************************ */
/*
 * @brief Initialize all the necessary peripheral and CeNTI devices.
 *
 * @param None.
 *
 * @return Indication if everything worked fine.
 * @retval RET_OK  - Everything worked fine.
 * @retval Other   - See et_RET.
 */
static et_RET Main__Initialize(void);

/*
 * @brief Function used to manage the loop flow.
 *
 * @param None.
 *
 * @return Indication if everything worked fine.
 * @retval RET_OK  - Everything worked fine.
 * @retval Other   - See et_RET.
 */
static et_RET Main__Loop(void);

/*
 * @brief Function used to check all the SoftTimers and enable its flag if its SoftTimer
 *          has elapsed.
 *
 * @param None.
 *
 * @return Indication if everything worked fine.
 * @retval RET_OK  - Everything worked fine.
 * @retval Other   - See et_RET.
 */
#if (defined(__CENTI_SOFTTIMER_IN_USE__))
    static void Main__CheckSoftTimers(void);
#endif


/* ************************************************************************************ */
/* * Private Functions Prototypes                                                     * */
/* ************************************************************************************ */
/*
 * @brief Function used to call the system device initialization function based on
 *          defines made on CeNTI/Defines/CeNTI.h file.
 *
 * @param None.
 *
 * @return Indication if everything worked fine.
 * @retval RET_OK  - Everything worked fine.
 * @retval Other   - See et_RET.
 */
static void Main__InitializeDevice(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  et_RET et_ret = RET_UNEXPECTED;

  /* Set initial state. */
  g_et_state = MAIN_STATE_INIT;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  switch (g_et_state)
	  {
      /* ********** Initialization error **************************************** */

      case MAIN_STATE_INIT_ERROR:

          CENTI_DEBUG__Error("Initialization failed!");
          CENTI_DEBUG__Info("Entering in an infinity loop!");

          /* Add code to handle the initialization error. */
          // ...

          while (1)
          {
              /* Stay here. */
          }

          break;

      /* ************************************************************************ */
      /* ********** Initialization ********************************************** */

      case MAIN_STATE_INIT:

          /* Initialize device. */
          et_ret = Main__Initialize();

          /* Add code if needed. */
          // ...

          /* If initialization was successfully complete, then go to loop state.
           * Otherwise, go to initialization error state. */
          if (RET_OK == et_ret)
          {
              g_et_state = MAIN_STATE_LOOP;
              break;
          }
          else
          {
              g_et_state = MAIN_STATE_INIT_ERROR;
              break;
          }

      /* ************************************************************************ */
      /* ********** Loop Error ************************************************** */

      case MAIN_STATE_LOOP_ERROR:

          CENTI_DEBUG__Error("Loop failed!");

          /* Add code to handle with a loop error. */
          // ...

          g_et_state = MAIN_STATE_LOOP;

      /* ************************************************************************ */
      /* ********** Loop ******************************************************** */

      case MAIN_STATE_LOOP:

          /* Go to initialization state to perform a soft reset. */
          if (FLAG_ON == f_soft_reset)
          {
              f_soft_reset = FLAG_OFF;

              CENTI_DEBUG__Warning("SoftReset!");

              g_et_state = MAIN_STATE_INIT;

              break;
          }

          /* Main Loop. */
          et_ret = Main__Loop();
          /* Check for any error. */
          if (RET_OK != et_ret)
          {
              g_et_state = MAIN_STATE_LOOP_ERROR;

              break;
          }

          /* Add code if needed. */
          // ...

          break;

      /* ************************************************************************ */
      /* ********** Default ***************************************************** */

      default:

          /* Reinitialize. */
          g_et_state = MAIN_STATE_INIT;

          break;

      /* ************************************************************************ */
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static et_RET Main__Initialize(void)
{
    et_RET et_ret      = RET_UNEXPECTED;
    int8_t num_retries = NUM_RETRIES;

    /* Initialize device. */
    Main__InitializeDevice();

    /* Initialize SoftTimer. */
    #if (defined(__CENTI_SOFTTIMER_IN_USE__))

        et_ret = SoftTimer__Initialize();
        CENTI_CHECK_RET(et_ret);

        /* Wait some time before initialize devices. */
        et_ret = SoftTimer__Delay_msec(DELAY_INIT_MS);
        CENTI_CHECK_RET(et_ret);

        CENTI_DEBUG__Info("SoftTimer initialization complete!");

    #endif

    do
    {
        /* Initialize Manager. */
        et_ret = Manager__Initialize();

        /* Check return. */
        if (et_ret != RET_OK)
        {
            /* Delay between retries. */
            #if (defined(__CENTI_SOFTTIMER_IN_USE__))
                SoftTimer__Delay_msec(DELAY_RETRY_MS);
            #endif

            /* Reduce the number of tries. */
            --num_retries;
        }
    }
    while ((et_ret != RET_OK) && (num_retries > 0));

    /* Check if return is not RET_OK. */
    CENTI_CHECK_RET(et_ret);

    CENTI_DEBUG__Info("Initialization complete!");

    return RET_OK;
}

static et_RET Main__Loop(void)
{
    et_RET et_ret = RET_UNEXPECTED;

    /* Check if any SoftTimer has occurred. */
    #if (defined(__CENTI_SOFTTIMER_IN_USE__))
        Main__CheckSoftTimers();
    #endif

    /* Perform the manager loop. */
    et_ret = Manager__Loop();
    CENTI_CHECK_RET(et_ret);

    /* Add code if needed. */
    // ...

    return RET_OK;
}

#if (defined(__CENTI_SOFTTIMER_IN_USE__))

    static void Main__CheckSoftTimers(void)
    {
        /* Add flags checks here. */
        for (uint8_t i=0; i<FLAGS_TOTAL; i++)
        {
            if (SOFTTIMER_ELAPSED_STATE_ELAPSED ==
                SoftTimer__Get_ElapsedState(ET_FLAG_SOFTTIMER_INSTANCES[i]))
            {
                *FLAGS[i] = FLAG_ON;
            }
        }
    }

#endif


/* ************************************************************************************ */
/* * Private Functions                                                                * */
/* ************************************************************************************ */
static void Main__InitializeDevice(void)
{
    #if (defined(__CENTI_CODE_CONFIGURATOR_MCC__))

        /* Initialize the device. */
        SYSTEM_Initialize();

        #if (CENTI_ENABLE_INTERRUPTS == CENTI_ENABLE)

            /* Enable global interrupts. */
            INTERRUPT_GlobalInterruptEnable();

        #else /* PROJECT_INTERRUPTS with wrong value. */

            /* Do nothing. */

        #endif /* PROJECT_INTERRUPTS */

	#elif (defined(__CENTI_CODE_CONFIGURATOR_MELODY__))

		/* Initialize the device. */
        SYSTEM_Initialize();

        #if (CENTI_ENABLE_INTERRUPTS == CENTI_ENABLE)

            /* Enable global interrupts. */
            INTERRUPT_GlobalInterruptEnable();

        #else

            /* Do nothing. */

        #endif

    #elif (defined(__CENTI_CODE_CONFIGURATOR_ATMEL_START__))

        /* Initialize the device. */
        atmel_start_init();

        #if (CENTI_ENABLE_INTERRUPTS == CENTI_ENABLE)

            /* Enable global interrupts. */
            ENABLE_INTERRUPTS();

        #else /* PROJECT_INTERRUPTS with wrong value. */

            /* Do nothing. */

        #endif /* PROJECT_INTERRUPTS */

    #elif (defined(__CENTI_CODE_CONFIGURATOR_HARMONY__))

		/* Initialize the device. */
		SYS_Initialize(NULL);

    #endif /* CENTI_CODE_CONFIGURATOR */
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
