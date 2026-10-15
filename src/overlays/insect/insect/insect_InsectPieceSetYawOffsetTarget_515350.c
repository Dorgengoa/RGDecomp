#include "types.h"
/* insect 0x00515350 -- 16 instructions, no frame.  `bc1fl` puts the
 * unconditional `p->mD0 = a` in its delay slot; the clamp is the fall-through
 * arm.  mD0 is RELOADED after the store, so the divisor's numerator is a
 * memory read and not the parameter still live in $f12. */

typedef struct Obj {
    u8  pad00[0xCC];
    f32 mCC;                        /* +0xCC */
    f32 mD0;                        /* +0xD0 */
    f32 mD4;                        /* +0xD4 */
} Obj;

void insect_InsectPieceSetYawOffsetTarget_515350(Obj *p, f32 a, f32 t)
{
    if (t <= 1.0f) {
        t = 1.0f;
    }
    p->mD0 = a;
    p->mD4 = (p->mCC - p->mD0) / t;
}
