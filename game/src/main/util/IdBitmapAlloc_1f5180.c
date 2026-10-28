/* rgp:protos */
#define RGP_SELF_IdBitmapAlloc_1f5180 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct Bits {
    s16 m00;
    s16 m02;
    u8 *m04;
    s32 m08;
} Bits;

/*rgp*/

s32 IdBitmapAlloc_1f5180(Bits *p)
{
    s32 n;
    s32 i;
    u8 m;

    if (p->m04 == 0) {
        return -1;
    }
    n = IdBitmapGetCount_1f50c0(p);
    for (i = 0; i < n; i++) {
        m = 1 << (i % 8);
        if (!(p->m04[i / 8] & m)) {
            p->m04[i / 8] = p->m04[i / 8] | m;
            return p->m00 + i;
        }
    }
    return -1;
}
