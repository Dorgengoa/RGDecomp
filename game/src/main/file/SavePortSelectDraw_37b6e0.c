/* rgp:protos */
#define RGP_SELF_SavePortSelectDraw_37b6e0 1
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

extern s32 D_004831D4;

void SavePortSelectDraw_37b6e0(s32 p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 l1;
    s32 h;

    t0 = D_004831D4;
    if (t0 != 0) {
        UiSetWidgetPos_290f60(t0, p2, 0x11B, 0x24);
        l1 = 0;
        do {
            h = l1 << 1;
            if (p0 == l1) {
                UiSetSpriteSizeUvSize_28f670(D_004831D4, p1, 0, 0, 0, 0, h);
                UiSetWidgetPos_290f60(D_004831D4, p2, ((l1 * 79) + 0x11B), 0x24);
            } else {
                UiSetSpriteSizeUvSize_28f670(D_004831D4, p1, 0x40, 0x1A, 4, 4, h);
            }
            l1 = (l1 + 1);
        } while (l1 < 2);
    }
    SaveSetPort_37b7c0(p0);
}
