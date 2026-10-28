/* rgp:protos */
#define RGP_SELF_NodeObjGetWorldBounds_194420 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8 pad000[0xA8];
    s32 mA8;
    u8 pad0AC[0x4];
    Vec4 mB0;
    Vec4 mC0;
} Obj;

/*rgp*/
/*rgp*/

s32 NodeObjGetWorldBounds_194420(Obj *p0, Vec4 *p1)
{
    Mtx4 m __attribute__((aligned(16)));

    if (p0->mA8 == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(p0, &m);
    AabbTransformBounds_13c710(p1, p1 + 1, &m, &p0->mB0, &p0->mC0);
    return 1;
}
