#include <PE_Servo180.h>
#include "main.h"
#include "led.h"
#include "tim.h"

typedef struct {
    GPIO_TypeDef *port;
    uint8_t      pin;
} Motor_Pin_t;

TIM_HandleTypeDef TIM_Handle;

PE_Servo180_Timer_t timer1;
PE_Servo180_Motor_t motor1 = {.ID = 0};

Motor_Pin_t motorPins[] = {
    {GPIOA, 0},
};

void SystemClock_Config(void);

void MX_GPIO_Init();

int main()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_LED_Init();
    MX_TIM_PWM_Init(TIM4, &TIM_Handle);

    PE_Servo180_attachMotor(&timer1, &motor1);

    PE_Servo180_setDegree(&motor1, 90);

    HAL_TIM_Base_Start_IT(&TIM_Handle);
    HAL_TIM_PWM_Start_IT(&TIM_Handle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&TIM_Handle, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start_IT(&TIM_Handle, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start_IT(&TIM_Handle, TIM_CHANNEL_4);

    uint32_t start = HAL_GetTick();

    int16_t diff = -1;
    uint16_t deg = 90;

    while (1) {
        if (HAL_GetTick() - start > 20) {
            start = HAL_GetTick();

            if (deg < 45) {
                deg = 45;
                diff = 1;
            }
            if (deg > 135) {
                deg = 135;
                diff = -1;
            }

            deg += diff;

            PE_Servo180_setDegree(&motor1, deg);
        }
        //MX_LED_ON(0);
        //HAL_Delay(500);
        MX_LED_OFF(0);
        //HAL_Delay(500);
    }
}

void PE_Servo180_setTimerOverflow(PE_Servo180_Timer_t *timer, uint16_t value) {
    __HAL_TIM_SET_AUTORELOAD(&TIM_Handle, value);
    (void) timer;
    (void) value;
}

void PE_Servo180_setTimerRefresh(PE_Servo180_Timer_t *timer) {
    HAL_TIM_GenerateEvent(&TIM_Handle, TIM_EVENTSOURCE_UPDATE);
    (void) timer;
}

void PE_Servo180_setMotorPin0(uint8_t id) {
    motorPins[id].port->BSRR = (1u << (motorPins[id].pin + 16u));
}

void PE_Servo180_setMotorPin1(uint8_t id) {
    motorPins[id].port->BSRR = (1u << motorPins[id].pin);
}

void TIM4_IRQHandler(void) {
    HAL_TIM_IRQHandler(&TIM_Handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *tim) {
    if (tim->Instance == TIM4) {
        MX_LED_ON(1);
        PE_Servo180_onOverflow(&timer1);
    }
}

//void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *tim) {
//    if (tim->Instance == TIM4) {
//        //MX_LED_ON(1);
//        //PE_Servo180_dispatch(&timer1);
//    }
//}

void MX_GPIO_Init() {
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO clock enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* GPIO Configuration */
    GPIO_InitStruct.Pin   = GPIO_PIN_0;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin   = GPIO_PIN_15;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 72000000
 *            HCLK(Hz)                       = 72000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 2
 *            APB2 Prescaler                 = 1
 *            HSE Frequency(Hz)              = 8000000
 *            HSE PREDIV1                    = 1
 *            PLL2MUL                        = 9
 *            Flash Latency(WS)              = 2
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    // Initializes the CPU clock source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }

    // Initializes the CPU, AHB and APB buses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK
                                  | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1
                                  | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler(__FILE__, __LINE__);
    }
}

/**
 * @brief  Initializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspInit(void)
{
    /* Alternate Function I/O clock enable */
    __HAL_RCC_AFIO_CLK_ENABLE();

    /* Power interface clock enable */
    __HAL_RCC_PWR_CLK_ENABLE();
}

/**
 * @brief  DeInitializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspDeInit(void)
{}

/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
        __NOP();
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

/**
 * @brief This function is executed in case of error occurrence.
 *
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void Error_Handler(const char * file, int line)
{
    UNUSED(file);
    UNUSED(line);

    const uint16_t sequence[] = {
            100,
            200,
            100,
            200,
            100,
            1200,
    };

    while (1) {
        MX_LED_PLAY(sequence, 6);
        __NOP();
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    UNUSED(file);
    UNUSED(line);
}
#endif
