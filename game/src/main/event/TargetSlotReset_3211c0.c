/* rgp:protos */
#define RGP_SELF_TargetSlotReset_3211c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    s32 m30;
    s32 m34;
    u8 pad038[0x4];
    s32 m3C;
    u8 pad040[0x10];
    u128 m50;
    u8 pad060[0x10];
    s32 m70;
};

void TargetSlotReset_3211c0(struct Obj0 *p0)
{
    s32 r0;

    r0 = (TargetRefClear_2e71d0(p0), (s32)0);
    p0->m34 = 0;
    p0->m30 = -1;
    p0->m70 = 0;
    p0->m3C = 0;
    memset((struct Obj0 *)((u8 *)p0 + 0x60), 0, 0x10);
    p0->m50 = 0;
}
