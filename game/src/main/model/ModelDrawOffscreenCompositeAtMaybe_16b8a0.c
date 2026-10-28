/* rgp:protos */
#define RGP_SELF_ModelDrawOffscreenCompositeAtMaybe_16b8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u128 m00;
};

struct Obj1 {
    u8 pad000[0x30];
    u128 m30;
};

int ModelDrawOffscreenCompositeAtMaybe_16b8a0(struct Obj1 *p0, s32 p1, struct Obj0 *p2, f32 fa0, f32 fa1)
{
    u128 t0;

    t0 = p2->m00;
    p0->m30 = t0;
    return ModelDrawOffscreenCompositeMaybe_16aac0(p0, p1, fa0, fa1);
}
