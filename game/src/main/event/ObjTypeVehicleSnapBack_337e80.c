/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleSnapBack_337e80 1
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
    u8 pad000[0x132];
    s16 m132;
};

s32 ObjTypeVehicleSnapBack_337e80(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 rv1;

    r0 = ObjTypeVehiclePlayBack_337ce0(p0, p1, p2, -1);
    rv1 = 1;
    if (r0 != 0) {
        rv1 = 0;
    } else {
        p0->m132 = 0x7FFF;
        rv1 = 1;
    }
    return rv1;
}
