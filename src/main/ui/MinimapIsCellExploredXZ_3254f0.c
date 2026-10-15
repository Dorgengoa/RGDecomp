#include "types.h"

extern void MinimapIsCellExplored_325550(void *a, u8 *buf, void *b, void *c);

void MinimapIsCellExploredXZ_3254f0(void *a, void *b, void *c, f32 x, f32 y)
{
    u8 buf[16];
    u8 *d;
    u32 n;

    d = buf;
    n = 0x10;
    if (d != 0) {
        do {
            *d = 0;
            n--;
            d++;
        } while (n != 0);
    }
    *(f32 *)&buf[0] = x;
    *(f32 *)&buf[8] = y;
    MinimapIsCellExplored_325550(a, buf, b, c);
}
