#include "types.h"
/* insect 0x005142D0 -- 76 bytes, 19 instructions, 3 calls, 1 conditional
 * branch.  The `lh 0x6C` sits in the delay slot of the FIRST call, i.e. it is
 * evaluated BEFORE it and kept in $16.  Naming the LOAD does not do that --
 * `k = o->f6C;` ahead of `func_1C4A90(func_1F5BE0(), k)` is byte-for-byte the
 * inline spelling's object (measured, 5 inert spellings incl. s16/s32/u16/an
 * initialiser/a pointer copy).  What pins it is naming the CALL: with
 * `e = func_1F5BE0();` as its own statement the load can no longer sink past
 * it.  Declaration order of `e` and `k` is inert.
 */

typedef struct Obj {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
} Obj;

extern f32 func_1ADD70(s32 h);
extern s32 func_1C4A90(s32 a, s16 b);
extern s32 func_1F5BE0(void);

f32 insect_InsectPieceGetMotionPhase_5142d0(Obj *o)
{
    s16 k;
    s32 e;
    s32 h;

    k = o->f6C;
    e = func_1F5BE0();
    h = func_1C4A90(e, k);
    if (h != 0) {
        return func_1ADD70(h);
    }
    return 0.0f;
}
