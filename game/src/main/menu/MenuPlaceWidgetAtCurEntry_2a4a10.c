/* rgp:protos */
#define RGP_SELF_MenuPlaceWidgetAtCurEntry_2a4a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 MenuPlaceWidgetAtCurEntry_2a4a10(struct Obj0 *p0, s32 p1, f32 fa0)
{
    s32 t0;
    s32 rv3;
    s32 r0;
    s32 rv2;
    s32 r1;

    t0 = p0->m04;
    rv3 = rv2;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        r0 = UiEntryListGetCurrentData_28ec60(t0);
        rv2 = 1;
        if (r0 == 0) {
            rv2 = 0;
        } else {
            r1 = UiPlaceWidgetAtCell_2a4a90(p0, p1, r0, fa0);
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
