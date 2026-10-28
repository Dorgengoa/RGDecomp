/* rgp:protos */
#define RGP_SELF_CharaCanTouchEvObjMaybe_2104c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA32];
    s16 mA32;
    s16 mA34;
    u8 padA36[0xE];
    s32 mA44;
};

s32 CharaCanTouchEvObjMaybe_2104c0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv1;
    s16 t1;
    s32 rv0;
    s16 t2;

    t0 = p0->mA44;
    rv1 = rv0;
    if ((t0 & 0x80000) != 0) {
        rv1 = 0;
    } else {
        t1 = p0->mA32;
        rv0 = (t2 == 3);
        if (t1 != 0x10) {
            rv0 = 1;
        } else {
            t2 = p0->mA34;
            rv0 = (t2 == 3);
        }
        rv1 = rv0;
    }
    return rv1;
}
