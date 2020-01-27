#include "stdio.h"
#include "string.h"

#include "FreeRTOS.h"
#include "task.h"

#if 0
#define os_printf(...)  printf("", _line_,);
#else
#define os_printf  printf
#endif

static xTaskHandle xTask_first;
static xTaskHandle xTask_second;

static void first_task(void *p)
{
    os_printf("%s\r\n", __FUNCTION__);
    int cnt = 0;

    while(1){
        os_printf("this is task11-%d\r\n", cnt++);
        vTaskDelay(2000);
    }
}

static void second_task(void *p)
{
    os_printf("%s\r\n", __FUNCTION__);
    int cnt = 0;

    while(1){
        os_printf("this is task22-%d\r\n", cnt++);
        vTaskDelay(4000);
    }
}

int main(void)
{
    portBASE_TYPE xReturn = pdPASS;

    os_printf("start \r\n");

    xReturn = xTaskCreate((pdTASK_CODE    )first_task, 
                          (const char *   )"first_task", 
                          (unsigned short )128, 
                          (void *         )NULL, 
                          (portBASE_TYPE  )tskIDLE_PRIORITY + 2, 
                          (xTaskHandle *  )&xTask_first);

    if (pdPASS != xReturn){
        return -1;
    }

    xReturn = xTaskCreate((pdTASK_CODE    )second_task, 
                          (const char *   )"second_task", 
                          (unsigned short )128, 
                          (void *         )NULL, 
                          (portBASE_TYPE  )tskIDLE_PRIORITY + 1, 
                          (xTaskHandle *  )&xTask_second);

    if (pdPASS != xReturn){
        return -1;
    }

    vTaskStartScheduler();

    while(1){
    }

    return 0;
}
