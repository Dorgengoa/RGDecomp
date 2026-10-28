/* rgp:protos */
#define RGP_SELF_TextEntryDialogHighlight_432f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

struct Obj1 {
    s32 m00;
};

s32 TextEntryDialogHighlight_432f50(struct Obj1 *p0, struct Obj0 *p1)
{
    s16 t0;
    s32 t1;
    s32 r0;
    s16 t2;
    s32 t3;
    s32 r1;

    t0 = p1->m10;
    t1 = p0->m00;
    r0 = ((s32)UiSetSpriteU_28f930(t1, 0x11, (0x7A - (((t0 * 0xC) + t0) << 2)), 0));
    t2 = p1->m10;
    t3 = p0->m00;
    r1 = ((s32)UiSetSpriteU_28f930(t3, 0x11, ((((t2 * 0xC) + t2) << 2) + 0x46), 1));
    return 1;
}
