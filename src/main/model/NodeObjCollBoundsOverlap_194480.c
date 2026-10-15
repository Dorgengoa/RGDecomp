#include "types.h"
#include "vec.h"

/* Stack locals are allocated in REVERSE declaration order, so the matrix at
   0x50 is declared first and the vector used as argument one (0x30) last.
   `sltu $2,$0,$2` on the tail is `!= 0` on the call's result. */

typedef struct Obj {
    u8 pad000[0xAC];
    s32 mAC;
    u8 pad0B0[0x30];
    Vec4 mE0;
    Vec4 mF0;
} Obj;

extern void NodeCalcWorldMatrix_186130(Obj *, Mtx4 *);
extern void AabbTransformBounds_13c710(Vec4 *, Vec4 *, Mtx4 *, Vec4 *, Vec4 *);
extern s32 AabbOverlap_13e0e0(Vec4 *, Vec4 *, Vec4 *, Vec4 *);

s32 NodeObjCollBoundsOverlap_194480(Obj *p0, Vec4 *p1)
{
    Mtx4 m;
    Vec4 b;
    Vec4 a;

    if (p0->mAC == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(p0, &m);
    AabbTransformBounds_13c710(&a, &b, &m, &p0->mE0, &p0->mF0);
    return AabbOverlap_13e0e0(&a, &b, p1, p1 + 1) != 0;
}
