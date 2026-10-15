#include "types.h"
typedef unsigned __int128 u128;
#pragma opt_propagation off
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct Vec3 { f32 x, y, z, w; } Vec3;
extern "C" void VecScale_13be00(Vec3 *, Vec3 *, f32);
extern "C" void VariantReadVec3_15f6c0(Vec3 *, s32);
extern "C" s32 VariantGetInt_15f780(s32);
extern void *D_004812DC;
static inline bool nz(s32 x) { return x != 0; }

extern "C" s32 MapCfgFuncFireData_18ae10(s32 arg0, s32 arg1)
{
    Vec3 v;
    s32 t;

    if (D_004812DC == 0) {
        return 0;
    }
    VariantReadVec3_15f6c0(&v, arg0);
    arg0 += 0x18;
    if (v.z + (v.x + v.y) == 0.0f) {
        v.x = 128.0f;
        v.y = 90.0f;
        v.z = 38.0f;
    } else {
        VecScale_13be00(&v, &v, 128.0f);
    }
    *(s32 *)&v.w = 0x43000000;
    *(u128 *)((u8 *)D_004812DC + 0x60) = *(u128 *)&v;
    t = arg0; arg0 += 8;
    S32(D_004812DC, 0x70) = !(bool)VariantGetInt_15f780(t);
    if (arg1 >= 5) {
        t = arg0; arg0 += 8;
        S32(D_004812DC, 0x74) = VariantGetInt_15f780(t);
    }
    if (arg1 >= 6) {
        t = arg0; arg0 += 8;
        S32(D_004812DC, 0x78) = VariantGetInt_15f780(t);
    }
    S32(D_004812DC, 0x7C) = -1;
    if (arg1 >= 7) {
        t = arg0; arg0 += 8;
        S32(D_004812DC, 0x7C) = VariantGetInt_15f780(t);
    }
    if (arg1 >= 8) {
        S32(D_004812DC, 0x80) = VariantGetInt_15f780(arg0);
    }
    return 1;
}
