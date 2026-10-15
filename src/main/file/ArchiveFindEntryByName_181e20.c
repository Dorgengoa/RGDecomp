#include "types.h"

extern s32 Strcasecmp_1345b8(void *arg0, s8 *arg1);

void *ArchiveFindEntryByName_181e20(void *arg0, s8 *arg1)
{
    s8 *name;
    u8 *e;
    s8 c;

    if (arg0 == NULL) {
        return NULL;
    }
    if (arg1 == NULL) {
        return NULL;
    }
    if (*arg1 == 0) {
        return NULL;
    }
    name = arg1;
    while ((c = *arg1) != 0) {
        if (c == 0x2F) {
            name = arg1 + 1;
        }
        arg1++;
    }
    for (e = (u8 *)arg0; *(s8 *)e != 0; e += *(s32 *)(e + 0x48)) {
        if (Strcasecmp_1345b8(e, name) == 0) {
            return e;
        }
    }
    return NULL;
}
