/* rg-override: replaces game/src/main/model/NodeObjIsInView_194200.c sha256 2f8d80b919b7a1ca2eae58a4abe89f21b9d06d20ce00663db828adcaa91219a5
 * why: draw-path random numbers (docs/WIDESCREEN.md "Draw-path random numbers", lane randdraw): the object is tested against the retail planes too and marked when only the port's wider planes let it in; the helpers are in the ViewSetPerspective_1564a0 override; no effect at 4:3 / 16:9 (no retail-plane set) */
/* rgp:protos */
#define RGP_SELF_NodeObjIsInView_194200 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8 pad000[0xA8];
    s32 mA8;
    u8 pad0AC[0x4];
    Vec4 mB0;
} Obj;

/*rgp*/
/*rgp*/

s32 rg_cull_retail_post(void *obj, void *box, void *world, s32 r);
void rg_cull_mark(void *obj, s32 r);

s32 NodeObjIsInView_194200(Obj *p0)
{
    s32 r;
    Mtx4 m __attribute__((aligned(16)));

    if (p0->mA8 == 0) {
        rg_cull_mark(p0, 0);
        return 0;
    }
    NodeCalcWorldMatrix_186130(p0, &m);
    r = CameraBoundsInView_15cd20(&p0->mB0, &m);
    return rg_cull_retail_post(p0, &p0->mB0, &m, r);
}
