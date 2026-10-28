/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemErrorMsgClose_38f190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 InsectCageMenuItemErrorMsgClose_38f190(s32 p0, s32 p1)
{
    UiSetWidgetsVisibleById_291110(p1, 0x75DA, 0, 1);
    InsectCageMenuSelectEntry_390d40(0x7534, 0);
    return 1;
}
