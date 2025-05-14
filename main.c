#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <ncurses.h>
#include "viewer.h"
#include "diskio.h"
#include "jump.h"
#include "mbr.h"
#include "gpt.h"
#include "search.h"
#include "editor.h"

#define SECTOR_SIZE 512

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: %s /dev/ada0\n", argv[0]);
		return 1;
	}

	int fd = open_disk(argv[1]);
	if(fd < 0){
		perror("open");
		return 1;
	}

	uint8_t buffer[SECTOR_SIZE];
	off_t sector = 0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	init_colors();

	while(1){
		if(read_sector(fd, sector, buffer) <= 0){
			mvprintw(LINES - 1, 0, "Failed to read sector %ld", sector);
			break;
		}

		draw_sector(buffer, sector, argv[1]);

		int ch = getch();
		if(ch == 'q') break;
		else if(ch == 'n' || ch == KEY_DOWN) sector++;
		else if((ch == 'p' || ch == KEY_UP) && sector > 0) sector--;
		else if(ch == 'j') sector = jump_to_sector();
		else if(ch == 'e') export_sector(buffer, sector);
		else if(ch == 'm' && sector == 0) parse_mbr(buffer);
		else if(ch == 'g' && sector == 1) parse_gpt(buffer);
		else if(ch == 's') sector = search_sector(fd, NULL, 0);
		else if(ch == 'x') edit_sector(buffer);
		else if(ch == 'w') write_sector(fd, sector, buffer);
	}

	endwin();
	close(fd);
	return 0;
}
