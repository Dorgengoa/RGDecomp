#include "types.h"

extern s32 sceOpen_11b928(char *path, s32 mode);
extern s32 sceLseek_11bd30(s32 fd, s32 off, s32 whence);
extern s32 sceRead_11bf70(s32 fd, void *buf, s32 size);
extern s32 sceClose_11bbb8(s32 fd);

s32 FileReadAll_1004b0(char *path, void *buf)
{
    s32 fd;
    s32 size = 0;
    fd = sceOpen_11b928(path, 1);
    if (fd >= 0) {
        size = sceLseek_11bd30(fd, 0, 2);
        sceLseek_11bd30(fd, 0, 0);
    }
    if (size > 0) {
        s32 n = size;
        size = sceRead_11bf70(fd, buf, size);
        if (size >= 0 && size != n) {
            size = -1;
        }
    }
    if (fd >= 0) {
        sceClose_11bbb8(fd);
    }
    return size;
}
