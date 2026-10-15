#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483938;
extern s32 D_0048393C;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

struct Obj1 {
    u8 pad000[0x8];
    s64 m08;
};

s32 OptionsSetGameData_3d6290(struct Obj1 *p0, struct Obj0 *p1)
{
    s32 rv0;
    s32 t0;

    rv0 = 1;
    if (p1 == 0) {
        rv0 = 0;
    } else {
        D_00483938 = p1;
        t0 = p1->m08;
        D_0048393C = t0;
        p0->m08 = 0;
        rv0 = 1;
    }
    return rv0;
}
