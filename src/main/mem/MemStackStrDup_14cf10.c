#include "types.h"

extern s32 strlen(const char *);
extern char *strcpy(char *, const char *);

typedef struct S14cf10 {
    u8 pad0[0x20];
    s32 f20;
    u8 pad24[0x28 - 0x24];
    s32 f28;
    s32 f2C;
    u8 pad30[0x34 - 0x30];
    s32 f34;
    u8 pad38[0x54 - 0x38];
    s32 f54;
} S14cf10;

char *MemStackStrDup_14cf10(char *p1, S14cf10 *p2)
{
    s32 len;
    u32 n;
    s32 q;
    char *result;
    s32 c;
    s32 total;

    if (p1 == 0) {
        return 0;
    }
    len = strlen(p1);
    n = len + 1;
    if (!(n & 0xF)) {
        q = n >> 4;
    } else {
        q = (n >> 4) + 1;
    }
    if (p2->f20 != 0) {
        result = 0;
    } else if (q <= 0) {
        result = 0;
    } else {
        c = p2->f2C;
        total = c + q;
        if (p2->f34 < total) {
            while (p2->f54 != 0) {
            }
            result = 0;
        } else {
            result = (char *)(p2->f28 + (c << 4));
            p2->f2C = total;
        }
    }
    if (result == 0) {
        return 0;
    }
    strcpy(result, p1);
    return result;
}
