/* rgp:protos */
#define RGP_SELF_NodeObjBasicCalcModelBounds_196ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* The `beql $2,$0` immediately after the `bnez $2` guard is a SECOND,
   redundant test of the same field in the source.
   The tail's sub-pointer has to be NAMED: retail loads 0x6C once and uses
   the same register for the test, the store and the call argument, which a
   re-read of `p0->m6C` across the store cannot produce. */

typedef struct Sub {
    u8 pad000[0x100];
    s32 m100;
} Sub;

typedef struct Obj {
    u8 pad000[0x6C];
    Sub *m6C;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NodeObjBasicCalcModelBounds_196ce0(Obj *p0, s32 p1)
{
    Mtx4 m __attribute__((aligned(16)));
    s32 r;
    Sub *s;

    if (p0->m6C == 0) {
        return 0;
    }
    if (p0->m6C != 0) {
        NodeCalcWorldMatrix_186130(p0, &m);
        ModelSetRootMatrix_1512e0(p0->m6C, &m);
    }
    r = ModelCalcBBox_151e20(p0->m6C, p1, 0);
    s = p0->m6C;
    if (s != 0) {
        s->m100 = 0;
        ModelDetachRootFrames_151460(s);
    }
    return r;
}
