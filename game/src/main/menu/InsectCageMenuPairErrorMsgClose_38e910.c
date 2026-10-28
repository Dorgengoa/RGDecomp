/* rgp:protos */
#define RGP_SELF_InsectCageMenuPairErrorMsgClose_38e910 1
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

extern s8 D_00483378;
extern u8 D_004E94C0[];

s32 InsectCageMenuPairErrorMsgClose_38e910(s32 p0, s32 p1)
{
    s8 t0;

    UiSetWidgetsVisibleById_291110(p1, 0x75DA, 0, 1);
    MenuCursorObjSetVisible_386280(D_004E94C0, 1);
    t0 = D_00483378;
    if (t0 == 0) {
        InsectCageMenuSelectEntry_390d40(0x7538, 0);
    } else {
        InsectCageMenuSelectEntry_390d40(0x7539, 0);
    }
    return 1;
}
