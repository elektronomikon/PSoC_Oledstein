#include "includes.h"
#include "math.h"


#define LVL_W 16
#define LVL_H 16
// mit 16x16 am 96x96 Display ergeben sich 6px/Spielfeld
#define PIXEL_PER_CELL (96/16)

unsigned char map[] = {
    1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
    1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,3,
    1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,3,
    1,0,0,0,1,1,0,0,2,0,0,0,0,0,0,3,
    1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
    1,0,0,0,0,0,0,0,3,3,3,1,0,0,0,3,
    1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,3,
    1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,3,
    1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,3,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
    1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
    1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,3,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
};


float  px, py, pa;
display_mode_t display_mode;

void init_oledstein() {
  px = 4.0f;
  py = 10.0f;
  pa = PI / 2.0f;
  display_mode = OLEDSTEIN_2D;
}

float absf(float x) {
  if (x < 0.0f)
  return -x;
  else
  return x;
}

int fov = 45;
int width = 96;
int height = 96;
int c = 1;



void draw_3dview() {
  volatile float dist;
  float wall_height;
  float fov = 90.0f * PI/180.0f;
  volatile float ray_angle;
  uint16_t color = 0x0000;
  
  while (pa > PI*2.0f)
    pa -= 2.0f * PI;

  for(int i = 0; i < width; i++) {
    float ray = (((float)i / width) * fov) + (pa - (fov/2.0f));
    float tx = sinf(ray);
    float ty = cosf(ray);
    float distance = 0;
    unsigned int hit = 0;
    while((!hit) && (distance < 16)) {
      distance += 0.1;
      int cx = (int)(px + (distance * tx));
      int cy = (int)(py - (distance * ty));
        if (cx < 0 || cx >= 16 || cy < 0 || cy >= 16) {
          hit = 1;
          distance = height;
        } else if (map[cx + (cy * 16)] == 1) {
          hit = 1;
           c = 1;
         distance *= fabs(cos(ray-pa));
        } else if (map[cx + (cy * 16)] == 2) {
           hit = 1;
           c = 2;
          distance *= fabs(cos(ray-pa));
        } else if (map[cx + (cy * 16)] == 3) {
          hit = 1;
          c = 3;
          distance *= fabs(cos(ray-pa));
        } else if (map[cx + (cy * 16)] == 4) {
           hit = 1;
          c = 4;
         distance *= fabs(cos(ray-pa));
        }
    }
    int ceiling = (height / 2) - (height / distance);
    int floor = height - ceiling;
    for(int z = 0; z < height; z++) {
        if (z <= ceiling) {
          color = 0x1230;
          oledc_pixel(&oledc, i, z, color);
        } else if (z > ceiling && z <= floor) {
          if (c == 1) {
             color = 0x3333;
          } else if (c==2) {
              color = 0x0103;
          } else if (c==3) {
              color = 0x0103;
          } else if (c==4) {
              color = 0x0caa;
          }
          oledc_pixel(&oledc, i, z, color);
       } else {
          color = 0x4caa;
          oledc_pixel(&oledc, i, z, color);
      }
    }
  }  
}

void draw_2dview() {
  float pdx, pdy;
  uint16_t box_w = OLEDC_SCREEN_WIDTH / LVL_W;
  uint16_t box_h = OLEDC_SCREEN_HEIGHT / LVL_H;

  while (pa > 2*PI)
    pa -= 2*PI;
  while (pa < 0.0f)
    pa += 2*PI;
  
  pdx = cosf(pa) * 3.0f;
  pdy = sinf(pa) * 3.0f;
  
  for (int y=0; y < LVL_H; y++) {
    for (int x=0; x < LVL_W; x++) {
      if (map[x + y*LVL_W] != 0) {
        oledc_rectangle(&oledc, x*box_w + 1, y*box_h + 1, (x+1)*box_w - 1 , (y+1)*box_h - 1, 0xFFFF);
      } else {
        oledc_rectangle(&oledc, x*box_w + 0, y*box_h + 0, (x+1)*box_w - 0, (y+1)*box_h - 0, 0x0000);
      }
    }
  }
  
  oledc_rectangle(&oledc, 6*px - 2 , 6*py - 2, 6*px + 4 , 6*py + 4, 0x9999);
  oledc_line(&oledc, 6*px , 6*py , 6*px + pdy*3, 6*py + pdx*3, 0x9999);
}
/* [] END OF FILE */
