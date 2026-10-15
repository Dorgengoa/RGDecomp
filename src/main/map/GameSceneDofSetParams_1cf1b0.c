#include "types.h"

extern void *memcpy(void *d, const void *s, s32 n);

void GameSceneDofSetParams_1cf1b0(u8 *p, s32 *src)
{
    s32 buf[5];
    s32 *d;
    s32 i;

    d = buf;
    i = 5;
    do {
        *d = *src;
        i--;
        src++;
        d++;
    } while (i > 0);
    *(s32 *)(p + 0x5968) = 1;
    memcpy(p + 0x596C, buf, 0x14);
}
