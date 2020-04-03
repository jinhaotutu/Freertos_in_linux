/**
  ******************************************************************************
  * @file    sem_app.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   message function
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 4: rtos_sem_4 ---> rtos_sem_4.bin
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "config.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_sem_post = NULL;
static TaskHandle_t task_sem_wait = NULL;
static SemaphoreHandle_t sem_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_sem_post_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_sem_post_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;

    while(1){
        os_printf("start post sem");

        xReturn = xSemaphoreGive(sem_demo);
        if (pdTRUE == xReturn){
            os_printf("post sem succeed");
        }else{
            os_printf("post sem error");
        }

        vTaskDelay(2500);
    }
}

/**
  * @brief  task_sem_wait_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_sem_wait_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;

    while(1){
        os_printf("wait sem");
        xReturn = xSemaphoreTake(sem_demo, portMAX_DELAY);
        if (pdTRUE == xReturn){
            os_printf("get sem succeed\r\n");
        }else{
            os_printf("get sem error\r\n");
        }
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

    sem_demo = xSemaphoreCreateBinary();
    if (NULL == sem_demo){
        return -1;
    }

    /* message task 队列接收任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_sem_post_cb,
                            (const char *   )"task_sem_post",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_sem_post);

    if (pdPASS != xReturn){
        return -1;
    }

    /* message task 队列发送任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_sem_wait_cb,
                            (const char *   )"task_sem_wait",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_sem_wait);

    if (pdPASS != xReturn){
        return -1;
    }

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/