#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>
#include <unistd.h>

off_t search_sector(int fd, const char *term, int is_hex);

#endif


