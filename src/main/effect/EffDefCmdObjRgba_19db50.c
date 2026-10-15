#include "types.h"
#include "vec.h"
/* EffDefCmdObjRgba_19db50 -- asm-free (s88m): the vu0inline.h Vu0CopyVectorXYZ helper is spelled with
 * mwcc VU0 intrinsics on file-scope vf0/vf1/vf2 register bindings.
 * - the double (s32) round trip on s keeps &v in a GPR (retail `addiu v0,sp,0x20; lqc2 vf2,0(v0)`).
 * - the trailing `if (ps) { ps = ...; }` under opt_dead_assignments off is a zero-word basic-block
 *   split standing in for the asm barrier: `li v0,1` stays after the sqc2 and p/&v colour v1/v0.
 * - bindings are `extern` so no .bss objects are emitted. */
#pragma opt_dead_assignments off

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz19db50 asm("vf0");
extern u128 va19db50 asm("vf1");
extern u128 vb19db50 asm("vf2");

static inline void CopyXYZ(void *d, void *s)
{
    u128 *pd = (u128 *)(u32)d;
    u128 *ps = (u128 *)(s32)(u32)s;
    ps = (u128 *)(s32)ps;
    va19db50 = *pd;
    vb19db50 = *ps;
    va19db50 = _vaddbc(va19db50, 0xE, vb19db50, vz19db50, 8);
    *pd = va19db50;
    if (ps) { ps = (u128 *)(s32)(u32)ps; }
}

typedef struct Obj {
    u8 pad0[0x20];
    s32 f20;
    u8 pad24[0x1C];
    u32 f40;
    void *f44;
} Obj;

extern void VariantReadVec3_15f6c0(Vec4 *, void *);
extern void *MemStackNew_14e230(s32, s32);
extern void *EffectParamCtorPos_19da60(void *);
extern void *EffectParamCtorRot_19da10(void *);
extern void *EffectParamCtorScl_19d9c0(void *);
extern void *EffectParamCtorCol_19d950(void *);
extern void *EffectParamCtorAlpha_19d900(void *);
extern void *EffectParamCtorTexUv_19d8b0(void *);
extern void *EffectParamCtorRgba_19d840(void *);

s32 EffDefCmdObjRgba_19db50(void *arg0, s32 arg1, Obj **arg2)
{
    Vec4 v;
    Obj *o;
    void *p;
    void *q;

    o = *arg2;
    o->f40 = 7;
    VariantReadVec3_15f6c0(&v, arg0);
    p = o->f44;
    switch ((s32)p) {
    case 0:
        switch (o->f40) {
        case 1:
            q = MemStackNew_14e230(0x40, o->f20);
            if (q != NULL) {
                q = EffectParamCtorPos_19da60(q);
            }
            o->f44 = q;
            break;
        case 2:
            q = MemStackNew_14e230(0x40, o->f20);
            if (q != NULL) {
                q = EffectParamCtorRot_19da10(q);
            }
            o->f44 = q;
            break;
        case 3:
            q = MemStackNew_14e230(0x40, o->f20);
            if (q != NULL) {
                q = EffectParamCtorScl_19d9c0(q);
            }
            o->f44 = q;
            break;
        case 4:
            q = MemStackNew_14e230(0x40, o->f20);
            if (q != NULL) {
                q = EffectParamCtorCol_19d950(q);
            }
            o->f44 = q;
            break;
        case 5:
            q = MemStackNew_14e230(0x40, o->f20);
            if (q != NULL) {
                q = EffectParamCtorAlpha_19d900(q);
            }
            o->f44 = q;
            break;
        case 6:
            q = MemStackNew_14e230(0x40, o->f20);
            if (q != NULL) {
                q = EffectParamCtorTexUv_19d8b0(q);
            }
            o->f44 = q;
            break;
        case 7:
            q = MemStackNew_14e230(0x40, o->f20);
            if (q != NULL) {
                q = EffectParamCtorRgba_19d840(q);
            }
            o->f44 = q;
            break;
        }
        p = o->f44;
    }
    if (p == NULL) {
        return 0;
    }
    CopyXYZ((u8 *)p + 0x20, &v);
    return 1;
}
