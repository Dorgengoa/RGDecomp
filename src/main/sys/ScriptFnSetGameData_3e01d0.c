#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

void ScriptFnSetGameData_3e01d0(struct Obj0 *p0)
{
    s32 t0;

    D_00483960 = p0;
    D_00483964 = 0;
    if (p0 != 0) {
        t0 = p0->m08;
        D_00483964 = t0;
    }
    D_00483968 = 0;
}
