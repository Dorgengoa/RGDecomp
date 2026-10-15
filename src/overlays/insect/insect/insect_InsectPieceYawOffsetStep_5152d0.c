#include "types.h"
/* insect 0x005152D0 -- 32 instructions.  A signed approach: the delta at
 * +0xD4 is read ONCE into a named local (it survives in $f1 across both
 * arms), the accumulator at +0xCC is re-loaded after every store, and 0.0f
 * lives in $f2 for the whole body. */

typedef struct Obj {
    u8 pad00[0xCC];
    f32 mCC;                        /* +0xCC */
    f32 mD0;                        /* +0xD0 */
    f32 mD4;                        /* +0xD4 */
} Obj;

void insect_InsectPieceYawOffsetStep_5152d0(Obj *o)
{
    f32 d;

    d = o->mD4;
    if (d > 0.0f) {
        o->mCC = o->mCC + d;
        if (o->mCC >= o->mD0) {
            o->mCC = o->mD0;
            o->mD4 = 0.0f;
        }
    } else if (d < 0.0f) {
        o->mCC = o->mCC + d;
        if (o->mCC <= o->mD0) {
            o->mCC = o->mD0;
            o->mD4 = 0.0f;
        }
    }
}
