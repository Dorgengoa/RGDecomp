#include "types.h"

extern s32 UiFindWidget_290460(s32, s32);
extern s32 memset(s32, s32, s32);
extern s32 strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UiSetWidgetTexName_290ac0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = UiFindWidget_290460(p0, p1);
    rv3 = 1;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        if (p2 == 0) {
            r1 = memset((r0 + 4), 0, 0x10);
        } else {
            r2 = strcpy((r0 + 4), p2);
        }
        rv3 = 1;
    }
    return rv3;
}
