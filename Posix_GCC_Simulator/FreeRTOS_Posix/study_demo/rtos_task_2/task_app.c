/**
  ******************************************************************************
  * @file    task_app.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   task function
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 2.second: rtos_task_2 ---> rtos_task_2.bin
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
static TaskHandle_t task_demo;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  freertos first creat task
  * @note   This function is used to creat app task and delect self.
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_demo_cb(void *p)
{
    os_printf("%s", __FUNCTION__);

    /* delay task 延时退出，并删除本任务 */
    while(1){
        os_printf("app task run");

        vTaskDelay(5000);
    }
}

/**
  * @brief  main
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
int app_task_init(void)
{
    portBASE_TYPE xReturn = pdPASS;

    os_printf("app task creat");

    /* first creat task in this 创建rtos第一个任务，用于创建其他任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_demo_cb,
                            (const char *   )"task_demo",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_demo);

    if (pdPASS != xReturn){
        return -1;
    }

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/