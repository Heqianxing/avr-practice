/*
imakew -f FIRST.mak
*/
#include <iom16v.h>
#include <macros.h>
#include "init_avr.h"
#include "led_send_display.h"
#include "key.h"


#pragma interrupt_handler timer0_comp_isr:iv_TIM0_COMP
void timer0_comp_isr(void)
{
	time++;
}

int __1(void *firs, void *last) { return 1; }
int __2(void *firs, void *last) { return -1; }

int main(void)
{
	long num = 0;
	unsigned char mask = 0;
	unsigned char len = 4;
	struct key key[2];
	int i;
	unsigned char key_num = sizeof(key) / sizeof(*key);
	key[0] = key_init(&PINA, 0x80, ~(1 << 7), 0, 0, __1, 0, __1);
	key[1] = key_init(&PIND, 0x08, ~(1 << 3), 0, 0, __2, 0, __2);

	init();
	while(1) {
		for (i = 0; i < key_num; i++) {
			key[i] = key_state_move(key[i]);
			num += key_operate(key[i], 0, 0);
			display_number(num, len, mask, &time);
		}
		display_number(num, len, mask, &time);
	}
	return 0;
}
