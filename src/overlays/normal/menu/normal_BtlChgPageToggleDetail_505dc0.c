#include "types.h"
/* normal 0x00505DC0 -- +0x70 setter/toggler.  `b != 0` writes `c` straight
 * through; otherwise the field is toggled.  Retail FALLS THROUGH to the
 * `= 0` store, so that is the source `if` body and `= 1` is the `else`; the
 * inverted spelling costs one word (10 vs 11) by turning the `beql` into a
 * `bnel` that swallows the `sb $0` in its delay slot. */

typedef struct Ctx { u8 pad000[0x70]; s8 f070; } Ctx;

s32 normal_BtlChgPageToggleDetail_505dc0(Ctx *p, s32 b, s8 c)
{
    if (b != 0) {
        p->f070 = c;
    } else if (p->f070 != 0) {
        p->f070 = 0;
    } else {
        p->f070 = 1;
    }
    return 1;
}
