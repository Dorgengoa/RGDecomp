#include "types.h"

extern s32 atoi(s8 *);
extern s32 strcmp(s8 *, s8 *);
extern s8 *strncpy(s8 *, s8 *, s32);
extern s8 *D_0044A610[];

s32 FilePathGetDeviceIndex_181a80(s8 *arg0)
{
    s8 *src;
    s8 sp20[0x1C];
    s32 i;
    s8 *dst;
    s64 c;
    s8 c2;
    s32 count;
    s8 sp3C[4];
    s8 *scan;
    s32 digits;

    scan = arg0;
    count = 0;
    while ((c = *scan) != 0) {
        if ((s64)((s64)c << 0x38) >> 0x38 == ':') {
            break;
        }
        scan++;
        count++;
    }
    if (c == 0) {
        return -1;
    }
    if (count >= 0x10) {
        return -1;
    }

    strncpy(sp20, arg0, count);
    sp20[count] = 0;
    dst = sp3C;
    src = sp20;
    digits = 0;
    while ((c2 = *src) != 0) {
        if (c2 >= '0' && c2 < ':') {
            digits++;
            *dst = c2;
            *src = 0;
            dst++;
            if (digits >= 3) {
                break;
            }
        }

        src++;
    }
    *dst = 0;
    for (i = 0; i < 5; i++) {
        if (strcmp(D_0044A610[i], sp20) == 0) {
            break;
        }
    }
    if (sp3C[0] != 0) {
        atoi(sp3C);
    }
    return i;
}
