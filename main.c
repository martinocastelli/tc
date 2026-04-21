#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include "tc.h"

static uint16_t terminal_size_x;
static uint16_t terminal_size_y;

void sigint_handler(int sig);
void sigwinch_handler(int sig);

int main(void) {
	srand(time(NULL));
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);

	tc_init();
	tc_set_echo_mode(false);
	tc_set_canonical_mode(false);
	tc_hide_cursor(true);

	tc_get_terminal_size(&terminal_size_y, &terminal_size_x);

	tc_erase_to_origin();
	fflush(stdout);

	uint16_t x = 2;
	uint16_t y = 2;

	tc_keyboard_input_d buff;
	
	tc_move_to(1, 1);
	putchar('a');
	tc_move_to(terminal_size_y, terminal_size_x);
	putchar('a');
	
	while(true) {
		tc_get_pressed_keys(&buff);
		tc_move_to(y, x);
		putchar(' ');
		for(size_t i = 0;i < buff.escape_input_size;i++) {
			switch(buff.escape_input[i]) {
				case TC_ARROW_UP: {
					if(y > 2) {
						y--;
					}
				} break;
				case TC_ARROW_DOWN: {
					if(y < terminal_size_y - 1) {
						y++;
					}
				} break;
				case TC_ARROW_LEFT: {
					if(x > 2) {
						x--;
					}
				} break;
				case TC_ARROW_RIGHT: {
					if(x < terminal_size_x - 1) {
						x++;
					}
				} break;
				default: {
				}
			}
		}
		// for(size_t i = 0;i < buff.normal_input_size;i++) {
		// 	switch(buff.normal_input[i]) {
		// 		case 'w': {
		// 			if(y > 1) {
		// 				y--;
		// 			}
		// 		} break;
		// 		case 's': {
		// 			if(y < 50) {
		// 				y++;
		// 			}
		// 		} break;
		// 		case 'a': {
		// 			if(x > 1) {
		// 				x--;
		// 			}
		// 		} break;
		// 		case 'd': {
		// 			if(x < 50) {
		// 				x++;
		// 			}
		// 		} break;
		// 		default: {
		// 		}
		// 	}
		// }
		tc_move_to(y, x);
		putchar('@');
		fflush(stdout);
		// usleep(100000);
	}
	sigwinch_handler(SIGWINCH);
	while(1){}
	tc_restore_defaults();
	return 0;
}

void sigint_handler(int sig) {
	tc_reset_font();
	tc_erase_to_origin();
	tc_hide_cursor(false);
	printf("termined with SIGINT\n");
	tc_restore_defaults();
	exit(0);
}

void sigwinch_handler(int sig) {
	uint16_t row, col;
	tc_get_terminal_size(&row, &col);
	terminal_size_x = col;
	terminal_size_y = row;
}
