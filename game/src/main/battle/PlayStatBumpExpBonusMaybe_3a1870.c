/* rgp:protos */
#define RGP_SELF_PlayStatBumpExpBonusMaybe_3a1870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004837C0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 PlayStatBumpExpBonusMaybe_3a1870(s32 p0)
{
    struct Obj0 * t0;
    s32 t1;
    s32 r0;
    u16 t2;

    t0 = D_004837C0;
    t1 = D_004837C0->m10;
    r0 = StateGetChapterIndexMaybe_3cd500(t1);
    t2 = *(u16 *)((u8 *)(r0 << 1) + p0 + 0xB72);
    *(s16 *)((u8 *)(r0 << 1) + p0 + 0xB72) = (t2 + 1);
    return 1;
}
