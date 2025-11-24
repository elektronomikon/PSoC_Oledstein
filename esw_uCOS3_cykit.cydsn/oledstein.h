/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "stdint.h"

extern float px,py,pa;

#define PI 3.14f

typedef enum {
  OLEDSTEIN_2D,
  OLEDSTEIN_3D,
} display_mode_t;

extern display_mode_t display_mode;

void init_oledstein();
void draw_2dview();
void draw_3dview();

float absf(float x);

/* [] END OF FILE */
