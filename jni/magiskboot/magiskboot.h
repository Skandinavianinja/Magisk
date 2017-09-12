#ifndef _MAGISKBOOT_H_
#define _MAGISKBOOT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#include "bootimg.h"
#include "sha1.h"
#include "magisk.h"
#include "utils.h"
#include "magic.h"

#define KERNEL_FILE     "kernel"
#define RAMDISK_FILE    "ramdisk.cpio"
#define SECOND_FILE     "second"
#define DTB_FILE        "dtb"
#define NEW_BOOT        "new-boot.img"

#define str(a) #a
#define xstr(a) str(a)

extern char *SUP_LIST[];
extern char *SUP_EXT_LIST[];
extern file_t SUP_TYPE_LIST[];

// Main entries
void unpack(const char *image);
void repack(const char* orig_image, const char* out_image);
void hexpatch(const char *image, const char *from, const char *to);
int parse_img(void *orig, size_t size);
int cpio_commands(const char *command, int argc, char *argv[]);
void cleanup();

// Compressions
void gzip(int mode, const char* filename, const void *buf, size_t size);
void lzma(int mode, const char* filename, const void *buf, size_t size);
void lz4(int mode, const char* filename, const void *buf, size_t size);
void bzip2(int mode, const char* filename, const void *buf, size_t size);
void lz4_legacy(int mode, const char* filename, const void *buf, size_t size);
int comp(file_t type, const char *to, const void *from, size_t size);
void comp_file(const char *method, const char *from, const char *to);
int decomp(file_t type, const char *to, const void *from, size_t size);
void decomp_file(char *from, const char *to);

// Utils
void mmap_ro(const char *filename, void **buf, size_t *size);
void mmap_rw(const char *filename, void **buf, size_t *size);
file_t check_type(const void *buf);
void get_type_name(file_t type, char *name);
void write_zero(int fd, size_t size);
void mem_align(size_t *pos, size_t align);
void file_align(int fd, size_t align, int out);
int open_new(const char *filename);

#endif
