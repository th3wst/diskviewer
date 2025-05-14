#include "diskio.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int open_disk(const char *path){
	return open(path, O_RDWR);
}

ssize_t read_sector(int fd, off_t sector, uint8_t *buffer){
	lseek(fd, sector * 512, SEEK_SET);
	return read(fd, buffer, 512);
}

int write_sector(int fd, off_t sector, const uint8_t *buffer){
	lseek(fd, sector * 512, SEEK_SET);
	return write(fd, buffer, 512);
}

int export_sector(const uint8_t *buffer, off_t sector){
	char fname[64];
	snprintf(fname, sizeof(fname), "sector_%08lx.bin", sector);
	FILE *f = fopen(fname, "wb");
	if (!f) return -1;
	fwrite(buffer, 1, 512, f);
	fclose(f);
	return 0;
}
