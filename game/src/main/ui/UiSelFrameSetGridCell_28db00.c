/* rgp:protos */
#define RGP_SELF_UiSelFrameSetGridCell_28db00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047EB30;
extern s32 D_0047EB40;

void UiSelFrameSetGridCell_28db00(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s16 t0;
    s16 t1;

    t0 = *(s16 *)((u8 *)&D_0047EB30 + (p2 << 1));
    t1 = *(s16 *)((u8 *)&D_0047EB40 + (p3 << 1));
    UiSelFrameSetRect_28db40(p0, p1, t0, t1, 0x28, 0x2E, p4, p5);
}
