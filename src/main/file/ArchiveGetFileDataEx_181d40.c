#include "types.h"

extern void *ArchiveFindEntryByName_181e20(void);

void *ArchiveGetFileDataEx_181d40(s32 arg0, s32 arg1, s32 *arg2, void **arg3)
{
    u8 *p;
    u8 *r;

    p = (u8 *)ArchiveFindEntryByName_181e20();
    if (p == NULL) {
        return NULL;
    }
    if (arg2 != NULL) {
        *arg2 = *(s32 *)(p + 0x44);
    }
    r = p + *(s32 *)(p + 0x40);
    if (arg3 != NULL) {
        *arg3 = NULL;
    }
    if ((*(s32 *)(p + 0x4C) == 0x270F) && (arg3 != NULL)) {
        *arg3 = p + 0x50;
    }
    return r;
}
