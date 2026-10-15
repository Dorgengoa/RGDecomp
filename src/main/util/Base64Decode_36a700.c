#pragma optimization_level 3
#include "types.h"

extern s32 strlen(u8 *);
extern void *memset(void *, s32, s32);

s32 Base64Decode_36a700(u8 *arg0, u8 *p)
{
    s32 len;
    s32 n;
    s32 i;
    s32 c;
    s32 v;
    s32 idx;
    s32 bit;

    len = strlen(p);
    if (len < 3) {
        return 0;
    }
    n = len * 6 / 8;
    for (i = 1; i <= 2; i++) {
        if (((s8 *)p)[len - 1] != 0x3D) {
            break;
        }
        len--;
        n--;
    }
    memset(arg0, 0, n);
    for (i = 0; i < len; i++) {
        c = *p++;
        if (c >= 0x41 && c < 0x5B) {
            v = c - 0x41;
        } else if (c >= 0x61 && c < 0x7B) {
            v = c - 0x47;
        } else if (c >= 0x30 && c < 0x3A) {
            v = c + 4;
        } else if (c == 0x2B) {
            v = 62;
        } else if (c == 0x2F) {
            v = 63;
        } else {
            v = 0;
        }
        idx = i * 6 / 8;
        bit = i * 6 % 8;
        if (idx < n) {
            arg0[idx] |= (v << bit) & 0xFF;
        }
        if (idx < n - 1) {
            arg0[idx + 1] |= (v >> (8 - bit)) & 0xFF;
        }
    }
    return n;
}
