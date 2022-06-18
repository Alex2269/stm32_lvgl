#ifndef __CONFIG_H
#define __CONFIG_H


#define USERTOS                                 0

#define _FB __attribute__ ((section(".data-buff")))
#define _CCMC __attribute__ ((section(".ccmram")))
#define _CCMD __attribute__ ((section(".ccmram-data")))

#define FB_SIZE 24

#define LV_DRV_INDEV_INCLUDE     <stdint.h>             /*Dummy include by default*/

#endif
