#include "jump.h"
#include <ncurses.h>
#include <stdlib.h>

off_t jump_to_sector(void){
	echo();
	char input[32];
	mvprintw(LINES - 2, 0, "Enter sector number: ");
	getnstr(input, sizeof(input) - 1);
	noecho();
	return strtoul(input, NULL, 10);
}
