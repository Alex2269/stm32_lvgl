
#include "touchpad.h"
#include "xpt2046.h"

// void get_point(TS_Point *p)
extern TS_Point p;

bool xpt2046_read(void)
{
  #define press_count 32
  static float x[press_count];
  static float y[press_count];
  static float sumx, sumy;

  for(uint16_t i = 0; i < press_count; i++)
  {
    get_point(&p);
//     if(p.z > 980)
//     {
//       data->state = LV_INDEV_STATE_REL; // EASED;
//       return false; /*No buffering now so no more data read*/
//     }
//     else
//     {
      x[i] = p.x;
      y[i] = p.y;
//     }

    sumx = sumy = 0;
    for(uint16_t i = 0; i < press_count; i++)
    {
      sumx += x[i];
      sumy += y[i];
    }
    p.x = sumx / press_count;
    p.y = sumy / press_count;

  }

  return false;
}

