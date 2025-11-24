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

#include "oledc.h"
#include "os.h"
#include "SPIM_1.h"

inline void smallest_delay(void) {
  for (volatile uint32_t i=0; i < 1; i++) {
    ;
  }
}

void spi_master_write(uint8_t *data_ptr, uint8_t len) {
  SPIM_1_PutArray(data_ptr, len);
  smallest_delay();
}

void spi_master_select_device(void) {
  CS_1_Write(0x00);
//  smallest_delay();
}

void spi_master_deselect_device(void) {
//  CS_1_Write(0xFF);
//  smallest_delay();
}

void digital_out_write(uint8_t pin, uint8_t val) {
  switch (pin) {
    case OLEDC_PIN_EN: // EN / INT_1
      if (val > 0)
        INT_1_Write(0xFF);
      else
        INT_1_Write(0x00);
      break;
    case OLEDC_PIN_DC: // DC
      PWM_1_Write(val);
      break;
    case OLEDC_PIN_RST: // RST
      RST_1_Write(val);
      break;
    case OLEDC_PIN_RW: // AN / RW
      AN_1_Write(val);
      break;
    default:
    ;
  }
  smallest_delay();
}

void digital_out_high(uint8_t pin) {
  switch (pin) {
    case OLEDC_PIN_EN: // EN / INT_1
      INT_1_Write(0xFF);
      break;
    case OLEDC_PIN_DC: // DC
      PWM_1_Write(0xFF);
      break;
    case OLEDC_PIN_RST: // RST
      RST_1_Write(0xFF);
      break;
    case OLEDC_PIN_RW: // AN /RW
      AN_1_Write(0xFF);
      break;
    default:
    ;
  }
  smallest_delay();
}


void digital_out_low(uint8_t pin) {
  switch (pin) {
    case OLEDC_PIN_EN: // EN / INT_1
      INT_1_Write(0x00);
      break;
    case OLEDC_PIN_DC: // DC / CS
      PWM_1_Write(0x00);
      break;
    case OLEDC_PIN_RST: // RST
      RST_1_Write(0x00);
      break;
    case OLEDC_PIN_RW: // AN /RW
      AN_1_Write(0x00);
      break;
    default:
    ;
  }
  smallest_delay();
}

void Delay_ms(uint32_t ms) {
  OS_ERR err;
			OSTimeDlyHMSM(0, 0, 0, ms, 
									OS_OPT_TIME_HMSM_STRICT, 
									&err);

}

void Delay_1ms() {
  OS_ERR err;
			OSTimeDlyHMSM(0, 0, 0, 1, 
									OS_OPT_TIME_HMSM_STRICT, 
									&err);

}

void Delay_100ms() {
  OS_ERR err;
    OSTimeDlyHMSM(0, 0, 0, 100, 
                  OS_OPT_TIME_HMSM_STRICT, 
                  &err);
}


/* [] END OF FILE */
