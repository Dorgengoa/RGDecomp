/* rgp:protos */
#define RGP_SELF_TextEntryUpdate_436640 1
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

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
};

s32 TextEntryUpdate_436640(struct Obj0 *p0)
{
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 t2;
    s32 rv3;
    s32 t3;
    s32 t4;

    t0 = p0->m00;
    if (t0 != 0) {
        UiUpdateWidgets_2913a0(t0);
        t1 = p0->m04;
        rv1 = t1;
    } else {
        t2 = p0->m04;
        rv1 = t2;
    }
    if (rv1 != 0) {
        UiEntryListUpdateNop_28ecc0();
        t3 = p0->m08;
        rv3 = t3;
    } else {
        t4 = p0->m08;
        rv3 = t4;
    }
    if (rv3 != 0) {
        StateMachineUpdate_28ed70(rv3);
    }
    return 0;
}
