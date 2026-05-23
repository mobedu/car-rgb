#ifndef  KEY_H_
#define  KEY_H_

#define key1                 0x80
#define key_null             0xF0  
#define key                  RA0

#define key_press            0x08
#define key_long             0x04
#define key_continue         0x02
#define key_up               0x01

#define key_status_init  	 1
#define key_status_wobble 	 2
#define key_status_press 	 3
#define key_status_long  	 4
#define key_status_continue  5
#define key_status_up        6

#define key_long_period      250			// 4ms * 500 = 2s
#define key_continue_period  5

void get_keyvalue(uint8_t *pkeyvalue);

#endif