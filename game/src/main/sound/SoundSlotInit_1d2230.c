/* rgp:protos */
#define RGP_SELF_SoundSlotInit_1d2230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0x4];
    s32 m14;
    u8 pad018[0x4];
    s16 m1C;
    s16 m1E;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
};

void SoundSlotInit_1d2230(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    r0 = (LoadHandleReset_1ccc10(p0), (s32)0);
    p0->m0C = -1;
    p0->m14 = -1;
    p0->m1C = -1;
    p0->m1E = 0;
    r1 = (MemStackClear_14dff0((struct Obj0 *)((u8 *)p0 + 0x30)), (s32)0);
    p0->m20 = 0x3F800000;
    p0->m2C = 0x3F800000;
    p0->m24 = 0xBF800000;
    p0->m28 = 0;
    SoundSlotFree_1d21e0(p0);
}
