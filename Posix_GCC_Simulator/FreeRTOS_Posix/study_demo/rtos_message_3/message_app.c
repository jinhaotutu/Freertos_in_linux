/**
  ******************************************************************************
  * @file    message_app.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   message function
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 3: rtos_message_3 ---> rtos_message_3.bin
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "config.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_msg_send = NULL;
static TaskHandle_t task_msg_rcv = NULL;
static QueueHandle_t queue_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  task_msg_send_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_msg_send_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    uint8_t msg_cnt = 0;
    uint8_t msg_buf[32] = {0};

    while(1){
        os_printf("start send message");

        memset(msg_buf, 0, 32);
        snprintf(msg_buf, 32, "this is send msg_cnt:%d", msg_cnt++);

        xReturn = xQueueSend(queue_demo, msg_buf, 0);
        if (pdTRUE == xReturn){
            os_printf("send message succeed");
        }else{
            os_printf("send message error");
        }

        vTaskDelay(2500);
    }
}

/**
  * @brief  task_msg_rcv_cb
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_msg_rcv_cb(void *p)
{
    os_printf("%s", __FUNCTION__);
    BaseType_t xReturn = pdTRUE;
    uint8_t recv_msg[32] = {0};

    while(1){
        os_printf("wait message");
        memset(recv_msg, 0, 32);
        xReturn = xQueueReceive(queue_demo, recv_msg, portMAX_DELAY);
        if (pdTRUE == xReturn){
            os_printf("recv message succeed:[%s]\r\n", recv_msg);
        }else{
            os_printf("recv message error\r\n");
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

    #define MSG_LEN     5
    #define MSG_SIZE    64
    queue_demo = xQueueCreate(  (UBaseType_t ) MSG_LEN,
                                (UBaseType_t ) MSG_SIZE);
    if (NULL == queue_demo){
        return -1;
    }

    /* message task 队列接收任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_msg_rcv_cb,
                            (const char *   )"task_msg_rcv",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_msg_rcv);

    if (pdPASS != xReturn){
        return -1;
    }
    
    /* message task 队列发送任务 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_msg_send_cb,
                            (const char *   )"task_msg_send",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_msg_send);

    if (pdPASS != xReturn){
        return -1;
    }

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/