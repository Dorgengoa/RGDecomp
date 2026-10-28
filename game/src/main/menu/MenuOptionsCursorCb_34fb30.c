/* rgp:protos */
#define RGP_SELF_MenuOptionsCursorCb_34fb30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482360;
extern s16 D_00482E84;
extern s16 D_00482E86;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
    s16 m12;
};

s32 MenuOptionsCursorCb_34fb30(struct Obj0 *p0)
{
    s16 t0;
    s16 t1;
    s16 t2;
    s32 t3;
    s32 r1;
    s16 t4;
    s16 t5;

    t0 = p0->m12;
    t1 = D_00482E86;
    if (t0 != t1) {
        MenuOptionLoadValue_350240(p0);
    }
    t2 = p0->m12;
    t3 = D_00482360;
    r1 = ((s32)UiSetWidgetPos_290f60(t3, 0x1B5, 0, (((t2 << 4) - t2) << 1)));
    t4 = p0->m10;
    D_00482E84 = t4;
    t5 = p0->m12;
    D_00482E86 = t5;
    return 1;
}
