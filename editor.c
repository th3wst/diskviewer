#include "editor.h"
#include <stdlib.h>
#include <ncurses.h>

void edit_sector(uint8_t *buffer){
	echo();
	char input[4];
	int offset = 0;
	mvprintw(LINES - 2, 0, "Edit byte offset (0-511): ");
	getnstr(input, 3);
	offset = atoi(input);

	if(offset < 0 || offset >= 512) return;
	mvprintw(LINES - 1, 0, "New value in hex (ex: 3F): ");
	getnstr(input, 3);
	uint8_t val = (uint8_t)strtol(input, NULL, 16);
	buffer[offset] = val;
	noecho();
}
