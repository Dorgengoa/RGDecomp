/* rgp:protos */
#define RGP_SELF_UiSetWidgetListVisibleById_28c190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void UiSetWidgetListVisibleById_28c190(s32 p0, s32 p1, s32 p2)
{
    s32 l0;

    if (p0 != 0) {
        l0 = 0;
        while (*(u16 *)((u8 *)p1 + (l0 << 1)) != 0xFFFF) {
            UiSetWidgetsVisibleById_291110(p0, *(u16 *)((u8 *)p1 + (l0 << 1)), (p2 & 0xFF), 1);
            l0 = (l0 + 1);
        }
        return;
    }
}
