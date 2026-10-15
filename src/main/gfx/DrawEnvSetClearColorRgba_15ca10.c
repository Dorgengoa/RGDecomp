#include "types.h"

/* A guarded inline byte-clear of the 16-byte local (the `beqz` on an obviously
   non-null stack address is in the SOURCE), then the four float arguments are
   written over it and the vector handed to DrawEnvSetClearColor_1449f0. */

extern void *D_004810A4;
extern void DrawEnvSetClearColor_1449f0(void *ctx, f32 *v);

void DrawEnvSetClearColorRgba_15ca10(f32 x, f32 y, f32 z, f32 w)
{
    f32 v[4];
    u8 *q;
    u32 n;

    q = (u8 *)v;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
    DrawEnvSetClearColor_1449f0(D_004810A4, v);
}
