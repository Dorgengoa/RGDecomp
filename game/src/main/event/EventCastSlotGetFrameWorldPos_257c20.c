/* rgp:protos */
#define RGP_SELF_EventCastSlotGetFrameWorldPos_257c20 1
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

s32 EventCastSlotGetFrameWorldPos_257c20(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    s32 rv6;
    s32 t1;
    s32 rv5;
    s32 r0;
    s32 rv4;
    s32 r1;
    s32 rv3;
    s32 r2;

    if (p1 < 0 || p1 >= 0x20) {
        return 0;
    }
    t0 = *(s32 *)((u8 *)p0 + (p1 << 4));
    if (t0 != 0) {
        rv6 = 0;
    } else {
        t1 = *(s32 *)((u8 *)p0 + (p1 << 4) + 0xC);
        if (t1 == 0) {
            rv5 = 0;
        } else {
            r0 = ModelGetRootFrame_1511a0(t1);
            if (r0 == 0) {
                rv4 = 0;
            } else {
                r1 = ((s32)FrameFindByName_149ed0(r0, p2));
                rv3 = 1;
                if (r1 == 0) {
                    rv3 = 0;
                } else {
                    r2 = (FrameGetWorldPos_148f30(r1, p3), (s32)0);
                    rv3 = 1;
                }
                rv4 = rv3;
            }
            rv5 = rv4;
        }
        rv6 = rv5;
    }
    return rv6;
}
