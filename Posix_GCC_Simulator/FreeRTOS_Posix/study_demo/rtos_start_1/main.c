#include "stdio.h"
#include "string.h"

#include "FreeRTOS.h"
#include "task.h"

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#define os_printf(_fmt_, ...) \
        printf("[log]%s:%d | "_fmt_"\r\n", __FILENAME__, __LINE__, ##__VA_ARGS__)

static TaskHandle_t xTask_creat;

static void creat_task(void *p)
{
    os_printf("%s", __FUNCTION__);
    int cnt = 0;

    /* creat app task in this */


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

int main(void)
{
    portBASE_TYPE xReturn = pdPASS;

    os_printf("Freertos v10.2.1 start ");

    xReturn = xTaskCreate(  (TaskFunction_t )creat_task,
                            (const char *   )"creat_task",
                            (unsigned short )128,
                            (void *         )NULL,
                            (UBaseType_t    )1,
                            (TaskHandle_t * )&xTask_creat);

    if (pdPASS != xReturn){
        return -1;
    }

    vTaskStartScheduler();

    while(1){
    }

    return 0;
}
