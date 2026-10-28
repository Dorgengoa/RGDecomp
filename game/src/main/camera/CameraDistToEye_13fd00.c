/* rgp:protos */
#define RGP_SELF_CameraDistToEye_13fd00 1
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
    u8 pad000[0xF20];
    s32 mF20;
};

f32 CameraDistToEye_13fd00(struct Obj0 *p0, void *rgp_a1)
{
    s32 t0;

    t0 = p0->mF20;
    if (t0 != 0) {
        return (f32)VecDistance_13d3d0((t0 + 0x170), (void *)rgp_a1);
        
    }
    return 0.0f;
}
