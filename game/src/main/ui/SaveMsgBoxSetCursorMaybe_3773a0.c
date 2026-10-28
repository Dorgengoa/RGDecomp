/* rgp:protos */
#define RGP_SELF_SaveMsgBoxSetCursorMaybe_3773a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u16 D_0047FB04;

void SaveMsgBoxSetCursorMaybe_3773a0(s32 p0, s32 p1)
{
    u16 t0;
    u16 t1;
    u16 t2;
    u16 t3;
    u16 t4;
    u16 t5;
    u16 t6;
    u16 t7;

    if (p0 != 0) {
        if (p1 == 0) {
            t0 = D_0047FB04;
            UiSetSpriteUvRect_28f9d0(p0, t0, 0x6C, 0xB4, 0x34, 0x1A, 9);
            t1 = D_0047FB04;
            UiSetSpriteUvRect_28f9d0(p0, t1, 0x38, 0xB4, 0x34, 0x1A, 0xA);
        } else {
            if (p1 == 1) {
                t2 = D_0047FB04;
                UiSetSpriteUvRect_28f9d0(p0, t2, 0x38, 0xB4, 0x34, 0x1A, 9);
                t3 = D_0047FB04;
                UiSetSpriteUvRect_28f9d0(p0, t3, 0x6C, 0xB4, 0x34, 0x1A, 0xA);
            } else {
                t4 = D_0047FB04;
                UiSetSpriteUvRect_28f9d0(p0, t4, 0x38, 0xB4, 0, 0, 9);
                t5 = D_0047FB04;
                UiSetSpriteUvRect_28f9d0(p0, t5, 0x38, 0xB4, 0, 0, 0xA);
                t6 = D_0047FB04;
                UiSetTextString_28f510(p0, t6, 0, 1);
                t7 = D_0047FB04;
                UiSetTextString_28f510(p0, t7, 0, 2);
            }
        }
        return;
    }
}
