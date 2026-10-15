#include "types.h"
#include "vec.h"

extern f64 Sqrt_129160(f64);
extern s32 dpmul(s64, s32);
extern void VecScale_13be00(f32 *, f32 *, f32);
extern void VariantReadVec3_15f6c0(f32 *, s64 *);
extern f32 VariantGetFloat_15f740(s64 *);
extern s32 VariantGetInt_15f780(s64 *);
extern f32 dptofp(s32);
extern s64 fptodp(f32);

extern f32 D_0047DCA4;
extern u8 *D_004812DC;

s32 MapCfgFuncPlightData_18abe0(s64 *p, s32 arg1)
{
    f32 v[4];
    f32 m;
    f32 m1;
    u16 t18;
    u8 *t19;

    if (D_004812DC == NULL) {
        return 0;
    }
    *(f32 *)(D_004812DC + 0x70) = VariantGetFloat_15f740(p++);
    VariantReadVec3_15f6c0(v, p);
    p += 3;
    *(s32 *)(D_004812DC + 0x78) = VariantGetInt_15f780(p++);
    if (*(s32 *)(D_004812DC + 0x78) == 4) {
        VecScale_13be00(v, v, D_0047DCA4);
    } else {
        VecScale_13be00(v, v, 0.5f);
    }
    v[3] = 0;
    m = (v[0] > v[1]) ? ((v[0] > v[2]) ? v[0] : v[2]) : ((v[1] > v[2]) ? v[1] : v[2]);
    t19 = D_004812DC;
    *(f32 *)(t19 + 0x74) = 0.25 * ((f64)*(f32 *)(t19 + 0x70) * Sqrt_129160(m));
    *(u128 *)(D_004812DC + 0x60) = *(u128 *)v;
    if (arg1 >= 6) {
        *(s32 *)(D_004812DC + 0x7C) = VariantGetInt_15f780(p++);
    }
    if (arg1 >= 7) {
        *(s32 *)(D_004812DC + 0x80) = VariantGetInt_15f780(p++);
    }
    if (arg1 >= 8) {
        *(s32 *)(D_004812DC + 0x84) = VariantGetInt_15f780(p++);
    }
    if (arg1 >= 9) {
        *(s32 *)(D_004812DC + 0x88) = VariantGetInt_15f780(p++);
    }
    if (arg1 >= 10) {
        *(s32 *)(D_004812DC + 0x8C) = VariantGetInt_15f780(p++);
    }
    if (arg1 >= 11) {
        *(f32 *)(D_004812DC + 0x90) = VariantGetFloat_15f740(p++);
    }
    if (arg1 >= 12) {
        *(f32 *)(D_004812DC + 0x94) = VariantGetFloat_15f740(p);
    }
    return 1;
}
