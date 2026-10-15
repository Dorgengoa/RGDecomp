#include "types.h"

typedef unsigned __int128 u128;

typedef struct Obj {
    s32 x0;
    s32 x4;
    u8 pad8[8];
    u8 x10[0x40];
    u8 x50[0x40];
    s32 x90;
    s32 *x94;
    u8 pad98[4];
    u8 (*x9C)[0x40];
    s32 xA0;
    s32 xA4;
    u128 *xA8;
    u128 *xAC;
    u128 *xB0;
} Obj;

extern void MtxTransformPoints_13c810(u128 *, void *, s32, s32);
extern void MtxInverse_13cf40(void *, void *);
extern void FrameCalcWorldMatrix_148ff0(s32, void *);

static inline s32 get(Obj *a, s32 j)
{
    s32 r;

    if (!(j >= 0 && j < a->x90)) {
        r = 0;
    } else {
        r = a->x94[j];
    }
    return r;
}

void DynClothResetToRest_16a340(Obj *arg0)
{
    u8 m[0x40];
    s32 i;
    s32 e;

    if (arg0->x0 == 0) {
        return;
    }
    if (arg0->xA0 == 0) {
        return;
    }
    if (arg0->x4 != 0) {
        FrameCalcWorldMatrix_148ff0(arg0->x4, m);
        MtxTransformPoints_13c810(arg0->xA8, m, arg0->xA4, arg0->xA0);
        FrameCalcWorldMatrix_148ff0(arg0->x4, arg0->x10);
        MtxInverse_13cf40(arg0->x50, arg0->x10);
    }
    for (i = 0; i < arg0->xA0; i++) {
        arg0->xB0[i] = 0;
        arg0->xAC[i] = arg0->xA8[i];
    }
    for (i = 0; i < arg0->x90; i++) {
        e = get(arg0, i);
        if (e != 0) {
            FrameCalcWorldMatrix_148ff0(e, arg0->x9C[i]);
        }
    }
    FrameCalcWorldMatrix_148ff0(arg0->x4, arg0->x10);
    MtxInverse_13cf40(arg0->x50, arg0->x10);
}
