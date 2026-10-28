/* rgp:protos */
#define RGP_SELF_McSetPortCardType_373110 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0047F9F0;
extern s32 D_00483178;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

void McSetPortCardType_373110(struct Obj0 *p0, s32 p1)
{
    s32 t0;

    if (p0 != 0) {
        t0 = p0->m04;
        *(s32 *)((u8 *)&D_00483178 + (p1 << 2)) = t0;
    } else {
        *(s32 *)((u8 *)&D_00483178 + (p1 << 2)) = 0;
    }
    D_0047F9F0 = 0;
}
