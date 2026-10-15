#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8 pad000[0xA8];
    s32 mA8;
    u8 pad0AC[0x4];
    Vec4 mB0;
} Obj;

extern void NodeCalcWorldMatrix_186130(Obj *, Mtx4 *);
extern s32 CameraBoundsInView_15cd20(Vec4 *, Mtx4 *);

s32 NodeObjIsInView_194200(Obj *p0)
{
    Mtx4 m;

    if (p0->mA8 == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(p0, &m);
    return CameraBoundsInView_15cd20(&p0->mB0, &m);
}
