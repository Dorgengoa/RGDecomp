/* rgp:protos */
#define RGP_SELF_HatenaMarkBindNode_345120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    u8 pad020[0x40];
    s32 m60;
    s32 m64;
    s32 m68;
    s32 m6C;
    u8 pad070[0x34];
    s32 mA4;
};

void HatenaMarkBindNode_345120(struct Obj0 *p0, s32 p1)
{
    p0->mA4 = p1;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m60 = 0;
    p0->m64 = 0;
    p0->m68 = 0;
    p0->m6C = 0;
    if (p1 != 0) {
        NodeGetTranslation_186650(p1, (struct Obj0 *)((u8 *)p0 + 0x10));
        NodeGetRotation_1865e0(p1, (struct Obj0 *)((u8 *)p0 + 0x60));
    }
}
