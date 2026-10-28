/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemErrorMsgShow_38f1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483304;
extern s16 D_00483364;

s32 InsectCageMenuItemErrorMsgShow_38f1d0(s32 p0, s32 p1)
{
    s32 t0;
    s16 t1;

    InsectCageMenuSetDrawFlag_390a80(2, 0);
    t0 = D_00483304;
    t1 = D_00483364;
    InsectCageMenuFormatMsgForCursor_388430((t0 + 0x800), t1);
    UiFitCenterWindow_388270(0x75DA, 1);
    UiSetWidgetsVisibleById_291110(p1, 0x75DA, 1, 1);
    return 1;
}
