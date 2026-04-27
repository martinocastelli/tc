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

	tc_create_text_font(1, false, false, false, false, TC_COLOR_DEFAULT, TC_COLOR_DEFAULT);
	tc_create_text_font(2, true, true, true, true, TC_RED, TC_BRIGHT_GREEN);

	tc_set_text_font(1);
	printf("hello\n");

	tc_set_text_font(2);
	printf("hello\n");

	tc_set_text_font(1);
	printf("hello\n");

	tc_set_text_font(2);
	printf("hello\n");

	tc_set_text_font(1);
	printf("hello\n");

	tc_set_text_font(2);
	printf("hello\n");

	
	tc_hide_cursor(false);
	tc_reset_font();
	putchar('\n');
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
