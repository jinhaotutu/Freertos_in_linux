/**
  ******************************************************************************
  * @file    main.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 1.first_demo: rtos_start_1 ---> rtos_start_1.bin
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

#include "config.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t xTask_creat;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  freertos first creat task
  * @note   This function is used to creat app task and delect self.
  * @param  *p
  * @param  None
  * @retval None
  */
static void creat_task(void *p)
{
    os_printf("%s", __FUNCTION__);
    int cnt = 0;

    /* creat app task in this 在这里创建应用任务 */


    /* creat app task in this 在这里创建应用任务 */

    /* delay task 延时退出，并删除本任务 */
    while(1){
        os_printf("this is creat task:idle-%d", cnt++);
        vTaskDelay(1000);

        if (cnt >= 10){
            break;
        }
    }

    os_printf("delete creat task");

    vTaskDelete(xTask_creat);
}

/**
  * @brief  main
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
int main(void)
{
    portBASE_TYPE xReturn = pdPASS;

    os_printf("Freertos v10.2.1 start ");

    /* first creat task in this 创建rtos第一个任务，用于创建其他任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )creat_task,
                            (const char *   )"creat_task",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&xTask_creat);

    if (pdPASS != xReturn){
        return -1;
    }

    /* start task 开启任务调度 */
    vTaskStartScheduler();

    while(1){
    }

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/