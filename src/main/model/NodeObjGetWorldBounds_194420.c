#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8 pad000[0xA8];
    s32 mA8;
    u8 pad0AC[0x4];
    Vec4 mB0;
    Vec4 mC0;
} Obj;

extern void NodeCalcWorldMatrix_186130(Obj *, Mtx4 *);
extern void AabbTransformBounds_13c710(Vec4 *, Vec4 *, Mtx4 *, Vec4 *, Vec4 *);

s32 NodeObjGetWorldBounds_194420(Obj *p0, Vec4 *p1)
{
    Mtx4 m;

    if (p0->mA8 == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(p0, &m);
    AabbTransformBounds_13c710(p1, p1 + 1, &m, &p0->mB0, &p0->mC0);
    return 1;
}
