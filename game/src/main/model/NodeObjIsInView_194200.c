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

s32 NodeObjIsInView_194200(Obj *p0)
{
    Mtx4 m __attribute__((aligned(16)));

    if (p0->mA8 == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(p0, &m);
    return CameraBoundsInView_15cd20(&p0->mB0, &m);
}
