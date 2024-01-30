#define _LED_C_
#include "led.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "oled.h"
#include "string.h"
#include "stdlib.h"

/** 
  * @brief ³õÊ¼»¯
  */
//void led_init()
//{
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOC, ENABLE);
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14 | GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);
//    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
//}

 void led_set_level(pLED_Class pthis, const int led_n, const led_bit led_level);
 void led_set_level_arr(pLED_Class pthis, const led_bits led_sta);

pLED_Class createLedClass(void){
	pLED_Class led_c = (pLED_Class)malloc(sizeof(LED_Class));
	if(led_c==NULL)
	{
		return NULL;
	
	}
	
	led_c -> led_amount=0;
	led_c -> led_curent_level= (led_bits)0;
	
	led_c -> set_level= led_set_level;
	led_c -> set_level_arr= led_set_level_arr;
	
	led_c -> set_level_arr(led_c,(led_bits)0x00);
	return led_c;
	
}
pLED_Class createLedClassWtihArgs(int led_amount){
	pLED_Class led_c = createLedClass();
	if(led_c==NULL)
	{
		return NULL;
	}
	
	led_c -> led_amount = led_amount ;
	return led_c;

}

void led_set_level(pLED_Class pthis, const int led_n, const led_bit led_level){
	led_out_gpio((uint8_t) led_level , led_n);
	pthis -> led_curent_level &= ~(0x1 << led_n );
	pthis -> led_curent_level |= ( led_level << led_n );
	
}

void led_set_level_arr(pLED_Class pthis, const led_bits led_sta){
	for(int i=0;i<pthis -> led_amount;++i)
	{
		led_out_gpio((uint8_t)(led_sta>>i)&1,i);
	
	}
		pthis -> led_curent_level = led_sta ;
	
}




	

