#ifndef DISKIO_H
#define DISKIO_H

#include <stdint.h>
#include <unistd.h>

int open_disk(const char *path);
ssize_t read_sector(int fd, off_t sector, uint8_t *buffer);
int write_sector(int fd, off_t sector, const uint8_t *buffer);
int export_sector(const uint8_t *buffer, off_t sector);

#endif
