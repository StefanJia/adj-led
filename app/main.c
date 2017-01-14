#include "common.h"
#include "init.h"
#include "global.h"
#define LIGHT 120

char t = 0;
int32 tt = 0;
int32 light = 0;
int32 pwm_output = 1000;


void delay(unsigned int t)
{
  t=t*1000000;
  while(t)
  {
    t--;
  }
}

void main()
{
  gpio_init();
  pit_init();
  adc_init();
  pwm_init();
  uart_init();
  OLED_Init(); 
  LCD_Fill(0x00);
  while(1){
    
    pwm_output = pid();
    if(pwm_output < 0){
      pwm_output = 0;
    }else if(pwm_output > 10000){
      pwm_output = 10000;
    }
    oledprintf(1,10,"light_ADC  %4d",light);
    oledprintf(3,10,"pwm_output  %7d",pwm_output);
    
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, pwm_output);
    
  }
  
  
	
}
int pid()
{
  int Kp = 2;
  int Ki = 2;
  int Kd = 2;
  static int powerout_I,last_error;
  int powerout = pwm_output;
  
  int error = LIGHT - light;
  int d_error = error - last_error; //两次偏差的变化量
  int powerout_p = Kp * error;    //比例输出
  int powerout_D = Kd * d_error;  //微分输出
  powerout_I += Ki * error;         //积分输出
  powerout = powerout_I + powerout_p + powerout_D;  //总输出
  last_error = error;    //偏差保存，供下次使用
  return powerout;
}

