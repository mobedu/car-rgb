#include <sc.h>
#include "config.h"
#include "key.h"

uint8_t key_scan(void) {
	if(key == 0) {
        return key1;
    }
    //if(key_other==0)return key2;
    //if(key_other1==0)return key3;
    return key_null;
}

/**********************************************************************************************************
单次按键：
 1.当检测到有按键按下时，进行约40ms滤波（每4ms检测一次）
 2.40ms后再次检测到按键是松开的，将重新返回到初始状态。
 3.40ms后再次检测到按键是按下的，将键值0x88放到pkeyvalue中
 4.当按键松开后，返回键值0x81

连续按键：
 1.当检测到有按键按下时，进行约40ms滤波（每4ms检测一次）
 2.40ms后再次检测到按键是松开的，将重新返回到初始状态。
 3.40ms后再次检测到按键是按下的，将键值0x88放到pkeyvalue中
 4.当检测到是长按键时，键值0x84
 5.当长按键检测完成后，进行到连按的状态，并返回键值0x82
 4.当按键松开后，返回键值0x81

 MARK：
 1.每4ms进入键值检测，并且在键值程序的开头，如有按键按下，最初返回的键值为0x80(即有按键按下）
   因此在主程序中，如果是连按，每隔4*key_continue_period时间返回键值0x82,在没有获得长按键值的时候
   键值函数返回的是0x80,0x88,0x84.
**********************************************************************************************************/
void get_keyvalue(uint8_t *pkeyvalue) {
	static uint8_t key_status = key_status_init;                           //将按键初始状态设定为没有按下的状态
    static uint8_t key_time_counter = 0;
    static uint8_t key_last_value = key_null;
    uint8_t key_temp = key_null;
	key_temp = key_scan();
    switch(key_status) {
        case key_status_init:                                          // 有按键按下
			if(key_temp != key_null) {
                key_status = key_status_wobble;
				key_time_counter = 0;
            }
            break;
        
        case key_status_wobble:
            key_status = key_status_press;
            break;

        case key_status_press:
            if(key_temp != key_null) {
                 if(++key_time_counter > 2) {                             // 确实有按键按下
                    key_time_counter = 0; 
                	key_last_value = key_temp;
					key_temp |= key_press;                              // key_temp=0x88
               		key_status = key_status_long;
					*pkeyvalue = key_temp;
                  }
             } else {
                key_status = key_status_init;
             }
             break;

        case key_status_long:
			 if(key_temp != key_null) {
                  key_time_counter++;
                  if(key_time_counter >= key_long_period) {
						key_time_counter = 0;
                        key_temp |= key_long;
                        key_status = key_status_continue;
						*pkeyvalue = key_temp;				// 立即更新
                    }
			   } else {
                key_status = key_status_up;
              }
              break;
         
         case key_status_continue:
              if(key_temp != key_null) {
                  key_time_counter++;
                  if(key_time_counter > key_continue_period) {
						key_time_counter = 0;
                        key_temp |= key_continue;
                    }
			   } else {
                key_status = key_status_up;
              }
              break;

		 case key_status_up:
              key_last_value |= key_up;
              key_temp = key_last_value;
              key_status = key_status_init;
              key_time_counter = 0;
              break;
        default:break; 
             
    }
    *pkeyvalue = key_temp;
}
