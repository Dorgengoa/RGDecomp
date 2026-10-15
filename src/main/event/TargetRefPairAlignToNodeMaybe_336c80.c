#include "types.h"
#include "vec.h"

typedef struct Mtx3 {
    Vec4 r[3];
} Mtx3;

extern void SrtMatMul_1c7470(Mtx3 *, Mtx4 *, Mtx4 *);
extern void SrtCtor48_1c7510(Mtx3 *);
extern void MatToRotPos_1cade0(Vec4 *, Vec4 *, Mtx4 *);
extern void MatMul_1cb700(Mtx4 *, Mtx4 *, Mtx4 *);
extern void VecNormalize_1cbb80(Vec4 *, Vec4 *);
extern s32 EventPathEvalXformByName_2e3d20(void *, Mtx3 *, s8 *, s32, s32);
extern void TargetRefDetachFromParent_2e5890(void *);
extern void TargetRefSetTranslation_2e5bf0(void *, Vec4 *);
extern void TargetRefSetRotation_2e5d10(void *, Vec4 *);
extern s32 TargetRefResolve_2e5ed0(void *);
extern void TargetRefGetMatrix_2e6870(void *, Mtx4 *);
extern s32 TargetRefGetObj_2e7110(void *);
extern s32 TargetRefPairGetMask_336fc0(void *);
extern void NodeCalcWorldMatrixThunk_186130(void *, Mtx4 *);
extern s8 *strcpy(s8 *, const s8 *);
extern s8 D_00462570[0x20];

s32 TargetRefPairAlignToNodeMaybe_336c80(u8 *obj, void *src, s8 *name, s32 val, u8 *list, s32 count, s32 bit)
{
    s8 buf[0x20];
    Mtx3 m;
    Mtx4 xf;
    Mtx4 rot;
    Vec4 pos;
    Vec4 dir;
    s32 r;
    s32 i;

    if (src == 0) {
        return 0;
    }
    if (TargetRefResolve_2e5ed0(obj + 0x30) == 0) {
        return 0;
    }
    if (*(void **)(obj + 0x60) == 0) {
        return 0;
    }
    if (bit < 0) {
        return 0;
    }
    if (!((1 << bit) & TargetRefPairGetMask_336fc0(obj))) {
        strcpy(buf, D_00462570);
        val = 10000;
    } else {
        strcpy(buf, name);
    }
    SrtCtor48_1c7510(&m);
    r = EventPathEvalXformByName_2e3d20(*(void **)(obj + 0x60), &m, buf, val, 0) & 0xFF;
    NodeCalcWorldMatrixThunk_186130(src, &rot);
    TargetRefGetMatrix_2e6870(obj + 0x30, &xf);
    MatMul_1cb700(&rot, &rot, &xf);
    VecNormalize_1cbb80(&rot.r[0], &rot.r[0]);
    VecNormalize_1cbb80(&rot.r[1], &rot.r[1]);
    VecNormalize_1cbb80(&rot.r[2], &rot.r[2]);
    SrtMatMul_1c7470(&m, &xf, &rot);
    MatToRotPos_1cade0(&pos, &dir, &xf);
    TargetRefDetachFromParent_2e5890(obj);
    TargetRefSetRotation_2e5d10(obj, &pos);
    TargetRefSetTranslation_2e5bf0(obj, &dir);
    if (list != 0 && count > 0) {
        for (i = 0; i < count; i++, list += 0x30) {
            if (TargetRefGetObj_2e7110(list) != 0) {
                TargetRefDetachFromParent_2e5890(list);
                TargetRefSetRotation_2e5d10(list, &pos);
                TargetRefSetTranslation_2e5bf0(list, &dir);
            }
        }
    }
    return r;
}
