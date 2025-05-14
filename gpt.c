#include "gpt.h"
#include <stdint.h>
#include <ncurses.h>
#include <string.h>
#include <inttypes.h>


void parse_gpt(const uint8_t *sector){
	if(memcmp(sector, "EFI PART", 8) != 0){
		mvprintw(LINES - 2, 0, "Invalid GPT header magic.");
		return;
	}
	else{
		uint32_t num_entries = *(uint32_t *)(sector + 80);
		uint32_t entry_size = *(uint32_t *)(sector + 84);
		uint64_t first_entry_lba = *(uint64_t *)(sector + 72);

		mvprintw(LINES - 4, 0, "GPT Detected: %u entries, Entry size:  %u, First LBA: %lu", num_entries, entry_size, first_entry_lba);
		refresh();
	}
}
