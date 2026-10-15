#include "types.h"

/* Guard order comes off the listing: beqz $6, beql $7, bnel $5 -- an `||`
   early return, with the `return 0` block placed BEFORE the copy.
   Zero-init store order is 0x00, 0x08, 0x04, 0x0C. */

typedef struct {
    s32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
} Rec;

s32 ActInfoMoveClone_231410(Rec *o, Rec *src, s32 a, s32 b)
{
    o->m00 = -1;
    o->m08 = 0.0f;
    o->m04 = 0.0f;
    o->m0C = 0.0f;
    if (a == 0 || b == 0 || src == 0) {
        return 0;
    }
    o->m00 = src->m00;
    o->m04 = src->m04;
    o->m08 = src->m08;
    o->m0C = src->m0C;
    return 1;
}
