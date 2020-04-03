/**
  ******************************************************************************
  * @file    timer_app.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   mutex function
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 8: rtos_timer_8 ---> rtos_timer_8.bin
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "config.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TimerHandle_t timer_1 = NULL;
static TimerHandle_t timer_2 = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void timer2_cb(void *p)
{
    os_printf("timer 2 run just once\r\n");
}

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void timer1_cb(void *p)
{
    static uint32_t timer_cnt = 0;

    timer_cnt++;

    os_printf("timer 1 run times:%d", timer_cnt);
    os_printf("system tick:%d\r\n", xTaskGetTickCount());
}

/**
  * @brief  app_init
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
int app_init(void)
{
    BaseType_t xReturn = pdPASS;

    os_printf("app task creat");

    timer_1 = xTimerCreate((const char *)"timer_1",
                            (TickType_t)2000,
                            (UBaseType_t)pdTRUE,
                            (void *)1,
                            (TimerCallbackFunction_t)timer1_cb);

    if (timer_1 == NULL){
        return -1;
    }

    xTimerStart(timer_1, 0);

    timer_2 = xTimerCreate((const char *)"timer_2",
                            (TickType_t)5000,
                            (UBaseType_t)pdFALSE,
                            (void *)2,
                            (TimerCallbackFunction_t)timer2_cb);

    if (timer_2 == NULL){
        return -1;
    }

    xTimerStart(timer_2, 0);

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/