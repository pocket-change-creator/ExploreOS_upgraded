
#include "vfs.hpp"
static const char page_index[] = "<html><body><h1>Explore Browser</h1><p>Local page from VFS.</p></body></html>";
static const char page_about[] = "<html><body><h2>About Explore</h2><p>Upgraded demo pages.</p></body></html>";
const VFile vfs_files[] = {
    {"index.html", page_index, sizeof(page_index)-1},
    {"about.html", page_about, sizeof(page_about)-1},
    {"readme.txt", "This is an embedded vfs file for Explore OS.", 42},
};
const int vfs_file_count = sizeof(vfs_files)/sizeof(vfs_files[0]);
const char* vfs_read(const char* name){
    for(int i=0;i<vfs_file_count;i++){ const VFile& f = vfs_files[i]; const char* n = f.name; int j=0; bool match=true; while(n[j]||name[j]){ if(n[j]!=name[j]){ match=false; break; } j++; } if(match) return f.data; } return nullptr;
}
