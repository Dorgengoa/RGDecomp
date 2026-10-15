#include "types.h"

/* idx range check is an ||; the name table is 16 slots of 32 bytes at
   +0x195D. */

extern u32 strlen(const char *s);
extern char *strcpy(char *d, const char *s);

void MesWinSetStrVar_276a00(void *o, s32 idx, const char *s)
{
    if (idx < 0 || idx >= 0x10) {
        return;
    }
    if (s == 0) {
        return;
    }
    if (strlen(s) >= 0x20) {
        return;
    }
    strcpy((char *)((u8 *)o + idx * 32 + 0x195D), s);
}
