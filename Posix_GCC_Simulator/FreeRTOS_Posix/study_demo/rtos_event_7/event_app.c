/**
  ******************************************************************************
  * @file    mutex_app.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   mutex function
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 7: rtos_event_7 ---> rtos_event_7.bin
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
#define EVENT_1_BIT     (0x01 << 0)
#define EVENT_2_BIT     (0x01 << 7)

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_event_rev1 = NULL;
static TaskHandle_t task_event_rev2 = NULL;
static TaskHandle_t task_event_post = NULL;

static EventGroupHandle_t event_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_event_rev2_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    EventBits_t event_t;

    while(1){
        event_t = xEventGroupWaitBits(event_demo, EVENT_1_BIT | EVENT_2_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        if (event_t & EVENT_1_BIT){
            os_printf("event recv2 num is event_1_bit:%02x", event_t);
        }else{
        }

        if (event_t & EVENT_2_BIT){
            os_printf("event recv2 num is event_2_bit:%02x", event_t);
        }else{
        }

        printf("\r\n");
    }
}

/**
  * @brief  task_event_rev_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_event_rev1_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    EventBits_t event_t;

    while(1){
        event_t = xEventGroupWaitBits(event_demo, EVENT_1_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        if (event_t & EVENT_1_BIT){
            os_printf("event recv1 num is event_1_bit:%02x\r\n", event_t);
        }else{
            os_printf("not match");
        }
    }
}

/**
  * @brief  task_event_post_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_event_post_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;

    while(1){
        vTaskDelay(1000);

        xEventGroupSetBits(event_demo, EVENT_1_BIT);

        vTaskDelay(2000);

        xEventGroupSetBits(event_demo, EVENT_2_BIT);

        vTaskDelay(3000);

        xEventGroupSetBits(event_demo, EVENT_1_BIT | EVENT_2_BIT);
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

    event_demo = xEventGroupCreate();
    if (NULL == event_demo){
        return -1;
    }

    /* event task 队列接收任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_event_rev1_cb,
                            (const char *   )"task_event_rev1",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_event_rev1);

    if (pdPASS != xReturn){
        return -1;
    }

    xReturn = xTaskCreate(  (TaskFunction_t )task_event_rev2_cb,
                            (const char *   )"task_event_rev2",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_event_rev2);

    if (pdPASS != xReturn){
        return -1;
    }

    /* event task 队列发送任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_event_post_cb,
                            (const char *   )"task_event_post",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_event_post);

    if (pdPASS != xReturn){
        return -1;
    }

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/