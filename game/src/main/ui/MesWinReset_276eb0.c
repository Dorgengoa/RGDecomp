/* rgp:protos */
#define RGP_SELF_MesWinReset_276eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1944];
    u8 m1944;
    u8 m1945;
    u8 pad1946[0x4AA];
    s32 m1DF0;
    s32 m1DF4;
};

void MesWinReset_276eb0(struct Obj0 *p0)
{
    u8 t0;

    MesWinClearState_277030(p0);
    t0 = p0->m1944;
    p0->m1945 = t0;
    p0->m1DF0 = 0xD;
    p0->m1DF4 = -1;
}
