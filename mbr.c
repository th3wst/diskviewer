#include "mbr.h"
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>

struct mbr_entry{
	uint8_t status;
	uint8_t chs_first[3];
	uint8_t type;
	uint8_t chs_last[3];
	uint32_t lba_start;
	uint32_t sectors;
} __attribute__((packed));

void parse_mbr(const uint8_t *sector){
	const struct mbr_entry *entries = (const struct mbr_entry *)(sector + 446);
	mvprintw(LINES - 5, 0, "MBR Partitions:");
	for(int i = 0; i < 4; i++){
		mvprintw(LINES - 4 + i, 0, "Entry %d: Type 0x%02X, Start LBA: %u, Sectors: %u", i + 1, entries[i].type, entries[i].lba_start, entries[i].sectors);
	}
	refresh();
}
