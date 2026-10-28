/* rgp:protos */
#define RGP_SELF_ActionPacketInitLoading_3e3a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483994;

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 m02;
    u8 m03;
    u8 pad004[0x8];
    s32 m0C;
};

struct Obj0 *ActionPacketInitLoading_3e3a90(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 r0;

    t0 = D_00483994;
    if (t0 == 0) {
        return (struct Obj0 *)0;
    }
    r0 = ((s32)ActionPacketClear_3e3e90(p0));
    p0->m02 = 2;
    p0->m03 = 0x35;
    p0->m00 = 2;
    p0->m0C = p1;
    return p0;
}
