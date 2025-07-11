#include <Arduino.h>
#include "Display_ST7789.h"
#include "LVGL_Driver.h"
#include "ui.h"

int curScr = 0;
int lastScr = 0;
bool btnRel = 1;
uint16_t Flash_Size;
const char* espModel;
char flash[32];

void Flash_test()
{
  printf("/********** RAM Test**********/\r\n");
  // Get Flash size
  uint32_t flashSize = ESP.getFlashChipSize();
  espModel = ESP.getChipModel();
  Flash_Size = flashSize/1024/1024;
  sprintf(flash, "%d MB", Flash_Size);
  printf("Flash size: %d MB \r\n", flashSize/1024/1024);
  printf("/******* RAM Test Over********/\r\n\r\n");
}

void setup()
{
  Flash_test();       
  LCD_Init();
  pinMode(9, INPUT);
  Lvgl_Init();
  ui_init();  
}

void loop()
{
  if(digitalRead(9) == LOW && btnRel) {
    btnRel = 0;
    printf("button pressed!\r\n");
    curScr++;
    if (curScr > 3) curScr = 0;
    printf("current active screen %d \r\n", curScr + 1);
    switch (curScr) {
    case 0:
      lv_disp_load_scr(ui_Screen1);
      break;
    case 1:
      lv_disp_load_scr(ui_Screen2);
      break;
    case 2:
      lv_disp_load_scr(ui_Screen3);
      break;
    case 3:
      lv_disp_load_scr(ui_Screen4);
      break;
    }
    printf("Switched to screen: %d \r\n", curScr + 1);
  }
  if (digitalRead(9) == 1) {
    btnRel = 1;
  }
  Timer_Loop();
  delay(5);
}
