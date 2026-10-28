/* rgp:protos */
#define RGP_SELF_CameraSetFogEnable_15cce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004810A4;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xF20];
    s32 mF20;
};

struct Obj1 {
    s32 m00;
};

void CameraSetFogEnable_15cce0(s32 p0)
{
    struct Obj0 * t0;
    struct Obj1 *rv0;
    s32 t1;

    t0 = D_004810A4;
    if (t0 == 0) {
        rv0 = 0;
    } else {
        t1 = D_004810A4->mF20;
        rv0 = (struct Obj1 *)t1;
    }
    rv0->m00 = p0;
}
