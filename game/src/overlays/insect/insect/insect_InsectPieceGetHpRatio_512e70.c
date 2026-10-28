/* rgp:protos */
#define RGP_SELF_insect_InsectPieceGetHpRatio_512e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512E70 -- 72 bytes, 18 instructions.  A guarded ratio of two s16
 * members; the zero the guard compares against is the same `mtc1 $0, $f0` that
 * is returned, and the float divide carries no zero trap.
 *
 * BOTH members are loaded and converted BEFORE the guard, so the divisor is a
 * named local too: written inline it sinks into the `bc1fl` delay slot and the
 * unit comes out two words short. */

typedef struct Obj {
    u8  pad00[0x1A];
    s16 f1A;                        /* +0x1A */
    u8  pad1C[0x1E - 0x1C];
    s16 f1E;                        /* +0x1E */
} Obj;

f32 insect_InsectPieceGetHpRatio_512e70(Obj *o)
{
    f32 a;
    f32 b;

    a = (f32)o->f1A;
    b = (f32)o->f1E;
    if (a <= 0.0f) {
        return 0.0f;
    }
    return a / b;
}
