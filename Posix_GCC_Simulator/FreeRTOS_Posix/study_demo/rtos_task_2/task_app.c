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
static TaskHandle_t task_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_demo_cb
  * @note   This function is used to run app task
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_demo_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    uint32_t cnt = 0x0fffffff;

    while(1){
        os_printf("app task run");

        while(cnt--);
        cnt = 0x0fffffff;

        vTaskDelay(1000);
    }
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

    /* app task in this 创建rtos应用任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_demo_cb,
                            (const char *   )"task_demo",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_demo);

    if (pdPASS != xReturn){
        return -1;
    }

    extern int cpu_task_init(void);
    cpu_task_init();

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/