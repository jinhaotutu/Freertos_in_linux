/**
  ******************************************************************************
  * @file    config.h
  * @author  Tuu
  * @version V1.0.0
  * @date    2020-01-28
  * @brief   config to demo define , function api
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"

/* Private define ------------------------------------------------------------*/
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#define os_printf(_fmt_, ...) \
        printf("[log ] %s:%d | "_fmt_"\r\n", __FILENAME__, __LINE__, ##__VA_ARGS__)


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __CONFIG_H */

/**
  * @}
  */

/******************************** (C) Tuu *********************END OF FILE****/