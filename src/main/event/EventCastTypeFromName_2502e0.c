#include "types.h"

extern s32 strcmp(const char *, const char *);
extern s32 D_0044CC40[99];

s32 EventCastTypeFromName_2502e0(s32 arg0)
{
    s32 buf[99];
    s32 *src;
    s32 *dst;
    s32 count;
    s32 i;

    src = D_0044CC40;
    dst = buf;
    count = 0x63;
    do {
        count -= 1;
        *dst = *src;
        src += 1;
        dst += 1;
    } while (count > 0);

    i = 0;
    while (i < 0xB) {
        if (strcmp((const char *) arg0, (const char *) buf + i * 0x24) == 0) {
            return *(s32 *)((u8 *) buf + i * 0x24 + 0x20);
        }
        i += 1;
    }
    return 0;
}
