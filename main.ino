
#include "ChainableLED.h"

#define NUM_OF_LED  1
#define YELLOW_INTERVAL 200
//板子上Ax是D（14+x）
//clk_pin A5 data_pin A4


ChainableLED leds(19, 18, NUM_OF_LED);

int sw1pin = 6; //这个是顺序模式开关
int sw2pin = 7; //黄灯闪烁开关
int sw3pin = 15;
int buzzlepin=10;

//乐谱


void setup() {
  pinMode(sw1pin, INPUT);
  pinMode(sw2pin, INPUT);
  leds.init();//初始化时已经设置灭
  leds.setColorRGB(0, 0, 0, 0);
  pinMode(buzzlepin,OUTPUT);
  //开机音乐
}
int key1val = 0;
int key2val = 0;
int key3val = 0;
int count1 = 0;
int count2 = 0;
void loop() {
  //控制信号
  if (!digitalRead(sw1pin)) {
    key1val = 1;
    if (key2val) {
      key2val = 0;
      count2 = 0;
    }
  }
  if (!digitalRead(sw2pin)) {
    key2val = 1;
    if (key1val) {
      key1val = 0;
      count1 = 0;
    }
  }
  if (key1val && !((count1 / YELLOW_INTERVAL) % 2))
    leds.setColorRGB(0, 255, 0, 180);
  if (key1val && ((count1 / YELLOW_INTERVAL) % 2))
    leds.setColorRGB(0, 0, 0, 0);
  if (key1val)
    ++count1;
  //正常切换
  if (key2val) {
    switch ((count2/500)%5) {
      case 0:
      case 1:
      leds.setColorRGB(0, 255, 0, 0); break;
      case 2:
        leds.setColorRGB(0, 255, 0, 180); break;
      case 3:
      case 4:
        leds.setColorRGB(0, 0, 0, 255);break;
    }


    ++count2;
  }
}
