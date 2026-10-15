#include "types.h"

typedef unsigned __int128 u128;

typedef struct Mat4 { f32 m[16]; } Mat4;
typedef struct Mat34 { f32 m[12]; } Mat34;

typedef union Vec4 {
    u128 q;
    f32 f[4];
    s32 i[4];
} Vec4;

extern void EvMapObjPartStep_363ba0(void);
extern void EvMapObjPartCalcMatrix_363a70(void *, Mat34 *);
extern void FrameCalcWorldMatrix_148ff0(void *, Mat4 *);
extern void sceVu0InversMatrix(Mat4 *, Mat4 *);
extern void sceVu0CopyVector(Vec4 *, Vec4 *);
extern void MtxMul_13d240(Mat34 *, Mat4 *, Mat34 *);
extern void ModelFrameSetMatrix_14a190(void *, Mat34 *);

s32 EvMapObjNodeApplyPartMatrixMaybe_367230(u8 *o)
{
    Vec4 va0;
    Mat34 m70;
    Mat4 m30;
    Vec4 v20;

    if (*(s32 *)(o + 0x144) == 0) {
        return 0;
    }
    EvMapObjPartStep_363ba0();
    EvMapObjPartCalcMatrix_363a70(o, &m70);
    v20.q = *(u128 *)(o + 0xF0);
    FrameCalcWorldMatrix_148ff0(*(void **)(*(u8 **)(o + 0x144) + 4), &m30);
    sceVu0InversMatrix(&m30, &m30);
    sceVu0CopyVector(&va0, &v20);
    va0.f[3] = 1.0f;
    MtxMul_13d240(&m70, &m30, &m70);
    ModelFrameSetMatrix_14a190(*(void **)(o + 0x144), &m70);
    return *(s32 *)(o + 0x138);
}
