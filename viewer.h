#ifndef VIEWER_H
#define VIEWER_H

#include <stdint.h>
#include <unistd.h>

void init_colors(void);
void draw_sector(uint8_t *buffer, off_t sector, const char *device);

#endif
