/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityHideAllPanels_341160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x5C];
    s32 m5C;
};

s32 MenuCharaAbilityHideAllPanels_341160(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;

    t0 = p0->m5C;
    UiSetWidgetVisible_290010(t0, 0x187, 0, -1);
    t1 = p0->m5C;
    UiSetWidgetVisible_290010(t1, 0x19E, 0, -1);
    return 1;
}
