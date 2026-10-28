/* rgp:protos */
#define RGP_SELF_InsectCageMenuSetCursorVisible_389d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483308;
extern s32 D_0048330C;

void InsectCageMenuSetCursorVisible_389d00(s32 p0)
{
    s32 t0;
    s32 t1;

    t0 = D_00483308;
    if (t0 != 0) {
        t1 = D_0048330C;
        UiSetWidgetVisible_290010(t1, 0x7602, p0, -1);
    }
}
