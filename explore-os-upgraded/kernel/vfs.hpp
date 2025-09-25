
#pragma once
#include <stdint.h>
struct VFile { const char* name; const char* data; uint32_t size; };
extern const VFile vfs_files[];
extern const int vfs_file_count;
const char* vfs_read(const char* name);
