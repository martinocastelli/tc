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

	tc_keyboard_input_d input;
	while(true) {

		char buff[STDIN_BUFF_SIZE];
		tc_read_raw_input_buffer(buff);
		for(size_t i = 0 ;buff[i] != '\0';i++) {
			switch(buff[i]) {
				case '\n':
					printf("ENTER");
					break;
				case '\t':
					printf("TAB");
					break;
				case '\033':
					printf("ESC");
					break;
				default:
					putchar(buff[i]);
			}
			putchar('\n');
		}


		// tc_get_pressed_keys(&input);
		// for(size_t i = 0;i < input.normal_input_size;i++) {
		// 	putchar(input.normal_input[i]);
		// 	putchar('\n');
		// }
		// for(size_t i = 0;i < input.escape_input_size;i++) {
		// 	switch(input.escape_input[i]) {
		// 		case TC_ARROW_UP:
		// 			printf("up\n");
		// 			break;
		// 		case TC_ARROW_DOWN:
		// 			printf("down\n");
		// 			break;
		// 		case TC_ARROW_RIGHT:
		// 			printf("right\n");
		// 			break;
		// 		case TC_ARROW_LEFT:
		// 			printf("left\n");
		// 			break;
		// 	}
		// }
		fflush(stdout);
		usleep(10000);
	}


	tc_hide_cursor(false);
	tc_set_canonical_mode(true);
	tc_set_echo_mode(true);
	tc_reset_font();
	putchar('\n');
	tc_restore_defaults();
	return 0;
}

void sigint_handler(int sig) {
	tc_reset_font();
	tc_erase_to_origin();
	tc_hide_cursor(false);
	tc_set_canonical_mode(true);
	tc_set_echo_mode(true);
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
