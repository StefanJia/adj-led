#ifndef GPIO_H
#define GPIO_H

void gpio_init(void);
void gpio_change(GPIO_Type *ptx, uint32 lsb_num, uint8 datal);
void pit_init(void);
void LED_isr(void);
void pit_isr(void);
void adc_init(void);
void pwm_init(void);
void uart_init(void);
int pid(void);
#endif