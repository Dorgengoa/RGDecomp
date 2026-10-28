/* rgp:protos */
#define RGP_SELF_CharaCmdShadowDraw_22cd50 1
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

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 CharaCmdShadowDraw_22cd50(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 rv4;
    s32 r0;
    s32 r1;
    s32 t0;
    s32 r2;
    s32 t1;
    s32 r3;

    rv4 = 1;
    if (p2 != 1) {
        rv4 = 0;
    } else {
        r0 = GetCurrentScene_1f5be0();
        r1 = ScriptArgGetInt_302d70(p1);
        if (r1 != 0) {
            t0 = p0->m00;
            r2 = ObjRecClearFlags_1c3dc0(r0, 1, t0, 0x20);
        } else {
            t1 = p0->m00;
            r3 = ((s32)ObjRecSetFlags_1c3e00(r0, 1, t1, 0x20));
        }
        rv4 = 1;
    }
    return rv4;
}
