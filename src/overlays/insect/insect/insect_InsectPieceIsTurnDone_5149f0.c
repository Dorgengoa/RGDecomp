#include "types.h"
/* insect 0x005149F0 -- 10 instructions.  mwcc builds `!=` on floats out of
 * `c.eq.s` plus `xori 1`; the trailing `andi 0xFF` is the u8 return.
 * MEASURED: the float TRUTHINESS test `!x` puts the member on the LEFT of the
 * `c.eq.s` (`c.eq.s $f1,$f0`); an explicit `x != 0.0f` -- and `x != 0`,
 * `(x != 0.0f) ^ 1`, and an s32 temp -- all put the zero on the left and cost
 * exactly that one word.  Swapping the operands IN THE SOURCE is INERT. */

typedef struct Obj {
    u8 pad00[0xC8];
    f32 mC8;                        /* +0xC8 */
} Obj;

u8 insect_InsectPieceIsTurnDone_5149f0(Obj *o)
{
    return !o->mC8;
}
