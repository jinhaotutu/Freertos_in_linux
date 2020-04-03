/**
  ******************************************************************************
  * @file    message_app.c
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   message function : post struct in message
  ******************************************************************************
  * @attention
  * Freertos run in the linux
  * 5: rtos_message_second_5 ---> rtos_message_second_5.bin
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "config.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef enum{
    MSG_ID_CNT,
    MSG_ID_TIME,
}MSG_ID_DEF;

typedef struct
{
    /* data */
    MSG_ID_DEF id;
    uint8_t data[128];
}MSG_DEF;

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TaskHandle_t task_msg_send_cnt = NULL;
static TaskHandle_t task_msg_send_time = NULL;
static TaskHandle_t task_msg_rcv = NULL;

static QueueHandle_t queue_demo = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

static int msg_post_data(MSG_ID_DEF id, uint8_t *data, uint32_t len)
{
    BaseType_t xReturn = pdTRUE;

    MSG_DEF *msg = pvPortMalloc(sizeof(MSG_DEF));
    if (NULL == msg){
        return -1;
    }

    memset(msg, 0, sizeof(MSG_DEF));
    msg->id = id;
    memcpy(msg->data, data, len);

    xReturn = xQueueSend(queue_demo, &msg, 0);
    if (pdTRUE == xReturn){
        os_printf("send message succeed");
    }else{
        os_printf("send message error");
    }

    return 0;
}

/**
  * @brief  task_msg_send_cnt_task
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_msg_send_cnt_task(void *p)
{
    os_printf("%s", __FUNCTION__);
    uint8_t msg_cnt = 0;
    uint8_t buf[32] = {0};

    while(1){
        os_printf("start send cnt message");

        memset(buf, 0, 32);
        snprintf(buf, 32, "this is send msg_cnt:%d", msg_cnt++);

        msg_post_data(MSG_ID_CNT, buf, strlen(buf));

        vTaskDelay(2500);
    }
}

/**
  * @brief  task_msg_send_cnt_task
  * @note   None
  * @param  *p
  * @param  None
  * @retval None
  */
static void task_msg_send_time_task(void *p)
{
    os_printf("%s", __FUNCTION__);
    uint8_t buf[32] = {0};

    while(1){
        os_printf("start send time message");

        memset(buf, 0, 32);
        snprintf(buf, 32, "this time is:%d", 512);

        msg_post_data(MSG_ID_TIME, buf, strlen(buf));

        vTaskDelay(4000);
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
    MSG_DEF *msg = NULL;

    while(1){
        // os_printf("wait message");

        xReturn = xQueueReceive(queue_demo, &msg, portMAX_DELAY);
        if (pdTRUE != xReturn){
            os_printf("recv message error\r\n");
            continue;
        }

        if (msg == NULL){
            continue;
        }

        switch(msg->id){
            case MSG_ID_CNT:
                os_printf("recv cnt message:[%s]\r\n", msg->data);
                break;
            case MSG_ID_TIME:
                os_printf("recv time message:[%s]\r\n", msg->data);
                break;
            default:
                break;
        }

        if (msg){
            vPortFree(msg);
            msg = NULL;
        }
    }
}

/**
  * @brief  app_msg_init
  * @note   None
  * @param  None
  * @param  None
  * @retval None
  */
int app_msg_init(void)
{
    BaseType_t xReturn = pdPASS;

    os_printf("app task creat");

    #define MSG_LEN     5
    #define MSG_SIZE    (sizeof(MSG_DEF*))
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

    /* message task 队列发送任务1 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_msg_send_cnt_task,
                            (const char *   )"task_msg_send_cnt",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_msg_send_cnt);

    if (pdPASS != xReturn){
        return -1;
    }

    /* message task 队列发送任务2 */
    xReturn = xTaskCreate(  (TaskFunction_t )task_msg_send_time_task,
                            (const char *   )"task_msg_send_time",
                            (unsigned short )512,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&task_msg_send_time);

    if (pdPASS != xReturn){
        return -1;
    }

    return 0;
}


/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/