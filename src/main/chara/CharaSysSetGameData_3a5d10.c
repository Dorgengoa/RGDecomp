#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004837C0;
extern s32 D_004837C4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 CharaSysSetGameData_3a5d10(s32 p0, struct Obj0 *p1)
{
    s32 rv0;
    s32 t0;

    rv0 = 1;
    if (p1 == 0) {
        rv0 = 0;
    } else {
        D_004837C0 = p1;
        t0 = p1->m08;
        D_004837C4 = t0;
        rv0 = 1;
    }
    return rv0;
}
