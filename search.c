#include "search.h"
#include "diskio.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SECTOR_SIZE 512

off_t search_sector(int fd, const char *term, int is_hex){
	char input[64];
	echo();
	mvprintw(LINES - 2, 0, "Enter search string: ");
	getnstr(input, sizeof(input) - 1);
	noecho();

	uint8_t buffer[SECTOR_SIZE];
	off_t sector = 0;
	while(read_sector(fd, sector, buffer) > 0){
		if(strstr((char *)buffer, input)){
			mvprintw(LINES - 3, 0, "Match found at sector %ld", sector);
			return sector;
		}
		sector++;
	}

	mvprintw(LINES - 3, 0, "No match found.");
	return sector;
}
