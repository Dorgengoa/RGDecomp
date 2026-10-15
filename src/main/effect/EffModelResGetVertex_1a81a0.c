#include "types.h"

typedef unsigned __int128 u128;

typedef struct S001A81A0 {
    u8 pad0[0x14];
    s32 f14;                  /* +0x14 */
    u128 *f18;                /* +0x18 */
} S001A81A0;

void EffModelResGetVertex_1a81a0(S001A81A0 *p, s32 i, u128 *out)
{
    if (i < 0 || i >= p->f14) {
        return;
    }
    *out = p->f18[i];
}
