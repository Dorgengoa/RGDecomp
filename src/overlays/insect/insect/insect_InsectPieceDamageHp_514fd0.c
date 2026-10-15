#include "types.h"
/* insect 0x00514FD0 -- 76 bytes.  The `return 0` is the FALL-THROUGH of the
 * test and the body sits after it, so the source guards with `n <= 0` and
 * returns early; the `n > 0` spelling puts the body first and is one word
 * short. */

typedef struct Obj {
    u8  pad00[0x1C];
    s16 f1C;                        /* +0x1C */
} Obj;

extern void insect_InsectPieceSetHp_512ee0(Obj *o, s32 n);

s32 insect_InsectPieceDamageHp_514fd0(Obj *o, s32 n)
{
    s32 r;

    if (n <= 0) {
        return 0;
    }
    r = o->f1C - n;
    if (r <= 0) {
        r = 0;
    }
    insect_InsectPieceSetHp_512ee0(o, r);
    return n;
}
