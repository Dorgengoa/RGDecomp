/* rgp:protos */
#define RGP_SELF_ModelObjGetScaledRadius_23b140 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0045B080;
extern f32 D_0047D82C;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4C8];
    f32 m4C8;
};

f32 ModelObjGetScaledRadius_23b140(struct Obj0 *p0)
{
    f32 t0;
    f32 t1;
    f32 t2;

    if (p0 != 0) {
        t0 = D_0045B080;
        t1 = D_0047D82C;
        t2 = p0->m4C8;
        return (t2 * (t1 * t0));
    }
    return 0.0f;
}
