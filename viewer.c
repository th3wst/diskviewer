#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "viewer.h"

#define SECTOR_SIZE 512
#define BYTES_PER_LINE 16

void init_colors(){
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_YELLOW, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_RED, COLOR_BLUE);

	bkgd(COLOR_PAIR(1));
	clear();
}

void draw_sector(uint8_t *buffer, off_t sector, const char *device){
	clear();
	attron(COLOR_PAIR(1));
	mvprintw(1, 0, "[Device: %s][SECTOR %ld] Keys: n/p: next/previous | j: jump | s: search | e: export | m: MBR | g: GPT | x: edit | w: write | q: quit", device, (intmax_t)sector);
	refresh();
	attroff(COLOR_PAIR(1));

	for(int i = 0; i < SECTOR_SIZE; i += BYTES_PER_LINE){
		attron(COLOR_PAIR(1));
		mvprintw(2 + i / BYTES_PER_LINE, 0, "%08X ", i);
		attroff(COLOR_PAIR(1));

		attron(COLOR_PAIR(2));
		for(int j = 0; j < BYTES_PER_LINE; ++j){
			printw("%02X ", buffer[i + j]);
		}
		attroff(COLOR_PAIR(2));

		printw(" ");

		attron(COLOR_PAIR(3));
		for(int j = 0; j < BYTES_PER_LINE; ++j){
			uint8_t c = buffer[i + j];
			addch((c >= 32 && c <= 126) ? c : '.');
		}
		attroff(COLOR_PAIR(3));
	}
	refresh();
}
