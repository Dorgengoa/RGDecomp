/* rgp:protos */
#define RGP_SELF_NodeRefObjMotionGateDefaultCtor_318440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471C90[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xB0];
    void *mB0;
    u8 pad0B4[0x7DC];
    u8 m890;
    u8 pad891[0x1F];
    s32 m8B0;
    s32 m8B4;
};

struct Obj0 *NodeRefObjMotionGateDefaultCtor_318440(struct Obj0 *p0)
{
    s32 r0;

    r0 = ((s32)NodeRefObjDefaultCtor_3190e0(p0));
    p0->mB0 = D_00471C90;
    p0->m890 = 0;
    p0->m8B0 = 0;
    p0->m8B4 = 0x3F800000;
    return p0;
}
