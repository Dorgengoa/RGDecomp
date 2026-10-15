#include "types.h"
typedef unsigned __int128 u128;
typedef struct S0016B970 {
    u8 pad00[0x4];
    s32 f4;
    u8 pad08[0x8];
    u128 q10;
    u128 q20;
} S0016B970;

s32 CollShapeGetBounds_16b970(S0016B970 *s, u128 *out)
{
    s32 r;

    if (s->f4 == 0) {
        r = 0;
    } else {
        r = 1;
        out[0] = s->q10;
        out[1] = s->q20;
    }
    return r;
}
