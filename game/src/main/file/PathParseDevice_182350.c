/* rgp:protos */
#define RGP_SELF_PathParseDevice_182350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(const s8 *, const s8 *);
extern s8 *strcpy(s8 *, const s8 *);
extern s8 *strncpy(s8 *, const s8 *, s32);
extern s8 D_00459730[0x10];
extern s8 D_00459740[0x10];
extern s8 D_00459750[0x10];
extern s8 D_00459758[0x10];
extern s8 D_00459760[0x10];
extern s8 D_00459768[0x10];

s32 PathParseDevice_182350(s8 *src, s8 *dst, s32 *out)
{
    s8 buf[0x10] __attribute__((aligned(16)));
    s8 *p;
    s32 n;
    s32 found;
    s8 c;

    if (src[1] == ':') {
        strcpy(dst, src);
        *out = 1;
        return -1;
    }
    p = src;
    n = 0;
    found = 0;
    while ((c = *p) != 0) {
        p++;
        n++;
        if (c == ':') {
            found = 1;
            break;
        }
    }
    if (found && n < 0x10) {
        strncpy(buf, src, n);
        buf[n] = 0;
    } else {
        buf[0] = 0;
    }
    if (*p != 0) {
        strcpy(dst, p);
    } else {
        strcpy(dst, src);
    }
    *out = 1;
    if (strcmp(buf, D_00459740) == 0) {
        return 0;
    }
    if (strcmp(buf, D_00459750) == 0) {
        return 0;
    }
    if (strcmp(buf, D_00459758) == 0) {
        return 1;
    }
    if (strcmp(buf, D_00459760) == 0) {
        return 2;
    }
    if (strcmp(buf, D_00459768) == 0) {
        return 3;
    }
    if (strcmp(buf, D_00459730) == 0) {
        return -1;
    }
    *out = 0;
    return -1;
}
