#include "common.h"
#include "init.h"
#include "global.h"

void gpio_init()
{
  
  GPIO_InitTypeDef gpio_init_blink_led1;         
  gpio_init_blink_led1.GPIO_PTx=PTC;             
  gpio_init_blink_led1.GPIO_Pins=GPIO_Pin0;
  gpio_init_blink_led1.GPIO_Dir=DIR_OUTPUT;       
  gpio_init_blink_led1.GPIO_Output=OUTPUT_H;      
  LPLD_GPIO_Init(gpio_init_blink_led1); 
  
  GPIO_InitTypeDef gpio_init_blink_led2;         
  gpio_init_blink_led2.GPIO_PTx=PTE;             
  gpio_init_blink_led2.GPIO_Pins=GPIO_Pin26;
  gpio_init_blink_led2.GPIO_Dir=DIR_OUTPUT;       
  gpio_init_blink_led2.GPIO_Output=OUTPUT_H;      
  LPLD_GPIO_Init(gpio_init_blink_led2); 
}

void pit_init(void)
{
  PIT_InitTypeDef pit0_init_struct={PIT0};
  pit0_init_struct.PIT_Pitx = PIT0;
  pit0_init_struct.PIT_PeriodMs = 50;
  pit0_init_struct.PIT_Isr = pit_isr;
  LPLD_PIT_Init(pit0_init_struct);
  LPLD_PIT_EnableIrq(pit0_init_struct);	
}

void adc_init(void)
{
  ADC_InitTypeDef adc1_init_struct;
  adc1_init_struct.ADC_Adcx = ADC1;             
  adc1_init_struct.ADC_DiffMode = ADC_SE;           //单端采集
  adc1_init_struct.ADC_BitMode = SE_10BIT;          //十位精度
  adc1_init_struct.ADC_LongSampleTimeSel = SAMTIME_SHORT;     //短时间
  adc1_init_struct.ADC_HwAvgSel = HW_8AVG;            //8次硬件平均
  adc1_init_struct.ADC_CalEnable = TRUE;               
  LPLD_ADC_Init(adc1_init_struct);
  LPLD_ADC_EnableIrq(adc1_init_struct);            //使能中断
  LPLD_ADC_Chn_Enable(ADC1, AD8);
  LPLD_ADC_Chn_Enable(ADC1, AD15);
}

void uart_init(void)
{
  UART_InitTypeDef uart1_init_struct;
  uart1_init_struct.UART_Uartx = UART1;
  uart1_init_struct.UART_BaudRate = 115200;
  uart1_init_struct.UART_RxIntEnable = TRUE;
  LPLD_UART_Init(uart1_init_struct);
  LPLD_UART_EnableIrq(uart1_init_struct);
}

void pwm_init(void)
{
  FTM_InitTypeDef ftm0_init_struct={FTM0};
  ftm0_init_struct.FTM_Ftmx = FTM0;
  ftm0_init_struct.FTM_Mode = FTM_MODE_PWM;
  ftm0_init_struct.FTM_PwmFreq = 150000;
  ftm0_init_struct.FTM_PwmDeadtimeCfg = DEADTIME_CH45;
  LPLD_FTM_Init(ftm0_init_struct);
  LPLD_FTM_PWM_Enable(FTM0 , FTM_Ch2, 10000, PTA5, ALIGN_LEFT);
  LPLD_FTM_PWM_Enable(FTM0 , FTM_Ch5, 10000, PTD5, ALIGN_LEFT);
}
  
  



  
  
  void pit_isr(void)
{
  
 
  light = LPLD_ADC_Get(ADC1, AD8);
  
  //if( light < 110 && pwm_output < 9500){
    //pwm_output+=500;
  //}else if( light > 120 && pwm_output > 500){
    //pwm_output-=500;
  //}
  pid();
  



 
 }

