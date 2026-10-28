extern "C" {
#pragma optimization_level 3
#include "types.h"

typedef rg_u128 u128;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Col18CB10;

extern void VecNormalize_13bd90(void *, void *);
extern void VecScale_13be00(void *, void *, f32);
extern void MatZero_13d2c0(void *);
extern f32 VecLength_13d4a0(void *);
extern void VecAddInPlace_13e070(void *, void *);
extern f32 Fabsf_18d120(f32);
extern void TimeOfDayLightCopy_18d140(u8 *, u8 *);
extern s32 TimeOfDayGetLightSet_18d290(u8 *, s32);
extern s32 TimeOfDayIsBlendEnabled_18d2a0(u8 *);
extern s32 TimeOfDayGetFixedIndex_18d2b0(u8 *);
extern void TimeOfDaySunDir_18d2d0(u8 *, f32 *);
extern s32 TimeOfDayCalcWeights_18d390(u8 *, f32 *);
extern s32 TimeOfDaySlot_18d7d0(u8 *);
extern u8 *ArrayGetChecked_1936d0(void *, s32);
extern f32 D_0047D5D0;
extern f32 D_0047D88C;

void TimeOfDayBlendLightSet_18cb10(u8 * raw_o,u8 * raw_out) {
u8 *o = raw_o;
u8 *out = raw_out;
    u8 *arr[12];
    f32 w[12] __attribute__((aligned(16)));
    u128 m170[4];
    u128 m130[4];
    union { u128 q; f32 f[4]; } acc120;
    u128 acc110;
    u128 acc100;
    u128 accF0;
    u128 accE0;
    u128 accD0;
    f32 t[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    s32 n;
    s32 k;
    s32 idx;
    s32 i;
    s32 cnt;
    s32 cc;
    s32 j;
    f32 *pw;
    u8 **pp;
    u8 *m;
    u8 *c;
    f32 *pw2;
    s32 q;
    u8 *fp;
    f32 r;

    if (out == 0) {
        return;
    }
    n = *(s32 *)(o + 0x1F8);
    if (!(TimeOfDayGetFixedIndex_18d2b0(o) < n) || TimeOfDayIsBlendEnabled_18d2a0(o) == 0) {
        k = TimeOfDayGetLightSet_18d290(o, TimeOfDayGetFixedIndex_18d2b0(o));
        if (k != 0) {
            TimeOfDayLightCopy_18d140(out, (u8 *)k);
            return;
        }
    }
    idx = TimeOfDaySlot_18d7d0(o);
    for (i = 0; i < n; i++) {
        pp = &arr[i];
        if ((*pp = ArrayGetChecked_1936d0(o + 0x70, i)) == 0) {
            return;
        }
    }
    TimeOfDayLightCopy_18d140(out, arr[idx]);
    if (*(s32 *)(o + 0x1F4) == 0) {
        return;
    }
    cnt = TimeOfDayCalcWeights_18d390(o, w);
    accF0 = 0;
    cc = 0;
    acc120.q = 0;
    accE0 = 0;
    accD0 = 0;
    acc110 = 0;
    acc100 = 0;
    MatZero_13d2c0(m170);
    MatZero_13d2c0(m130);
    for (j = 0; j < cnt; j++) {
        pw = &w[j];
        if (*(volatile f32 *)pw <= 0.0f) {
            continue;
        }
        pp = &arr[j];
        m = *pp;
        VecScale_13be00(t, m + 0x180, w[j]);
        VecAddInPlace_13e070(&acc120, t);
        VecScale_13be00(t, m + 0x10, w[j]);
        VecAddInPlace_13e070(&acc110, t);
        VecScale_13be00(t, m + 0x20, w[j]);
        VecAddInPlace_13e070(&acc100, t);
        VecScale_13be00(t, m + 0x190, w[j]);
        VecAddInPlace_13e070(&accF0, t);
        if (*(s32 *)(m + 0x1A0) != 0) {
            c = *(u8 **)((u32)((u8 *)arr + j * 4));
            t[0] = (u32)((Col18CB10 *)(c + 0x1AC))->r;
            t[1] = (u32)((Col18CB10 *)(c + 0x1AC))->g;
            t[2] = (u32)((Col18CB10 *)(c + 0x1AC))->b;
            t[3] = (u32)((Col18CB10 *)(c + 0x1AC))->a;
            VecScale_13be00(t, t, w[j]);
            VecAddInPlace_13e070(&accD0, t);
            t[0] = *(f32 *)(c + 0x1A4);
            t[1] = *(f32 *)(c + 0x1A8);
            t[2] = *(f32 *)(c + 0x1B8);
            t[3] = *(f32 *)(c + 0x1BC);
            VecScale_13be00(t, t, w[j]);
            VecAddInPlace_13e070(&accE0, t);
            cc++;
        }
        for (q = 0; q < 4; q++) {
            VecScale_13be00(t, m + q * 16 + 0x30, w[j]);
            VecAddInPlace_13e070(&m170[q], t);
            VecScale_13be00(t, m + q * 16 + 0x70, w[j]);
            VecAddInPlace_13e070(&m130[q], t);
        }
    }
    r = Fabsf_18d120(acc120.f[3] - 128.0f);
    if (r < D_0047D88C) {
        acc120.f[3] = 128.0f;
    }
    *(u128 *)(out + 0x180) = acc120.q;
    *(u128 *)(out + 0x190) = accF0;
    *(u128 *)(out + 0x10) = acc110;
    *(u128 *)(out + 0x20) = acc100;
    *(u128 *)(out + 0x70) = m130[0];
    for (q = 0; q < 4; q++) {
        if (!(VecLength_13d4a0(&m170[q]) <= 0.0f)) {
            VecNormalize_13bd90(out + 0x30 + q * 16, &m170[q]);
        }
        *(u128 *)(out + 0x70 + q * 16) = m130[q];
    }
    TimeOfDaySunDir_18d2d0(o, v);
    VecNormalize_13bd90(v, v);
    {f32 current=*(volatile f32 *)&v[1];f32 limit=D_0047D5D0;if(current<limit){v[1]=limit;VecNormalize_13bd90(v,v);}}
    *(f32 *)(out + 0x30) = v[0];
    *(f32 *)(out + 0x34) = v[1];
    *(f32 *)(out + 0x38) = v[2];
    ((Col18CB10 *)(out + 0x1AC))->r = ((f32 *)&accD0)[0];
    ((Col18CB10 *)(out + 0x1AC))->g = ((f32 *)&accD0)[1];
    ((Col18CB10 *)(out + 0x1AC))->b = ((f32 *)&accD0)[2];
    ((Col18CB10 *)(out + 0x1AC))->a = ((f32 *)&accD0)[3];
    *(f32 *)(out + 0x1A4) = ((f32 *)&accE0)[0];
    *(f32 *)(out + 0x1A8) = ((f32 *)&accE0)[1];
    *(f32 *)(out + 0x1B8) = ((f32 *)&accE0)[2];
    *(f32 *)(out + 0x1BC) = ((f32 *)&accE0)[3];
    *(s32 *)(out + 0x1A0) = 0 < cc;
}

}
