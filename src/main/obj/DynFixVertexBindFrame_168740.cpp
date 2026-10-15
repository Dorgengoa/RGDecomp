#include "types.h"
#include "vec.h"

typedef struct {
    u8 pad0[0xC];
    f32 unkC;
    s32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Obj00168740;

struct Glob00168740 {
    u8 pad0[0x90];
    s32 unk90;
    s32 *unk94;
    u8 pad98[0xA0 - 0x98];
    s32 unkA0;
    u8 *unkA4;
    u8 pada8[0xBC - 0xA8];
    s32 unkBC;
    u8 *unkC0;
    Obj00168740 *getObj(s32 i) {
        if (i < 0 || i >= unkBC) return 0;
        return (Obj00168740 *)(unkC0 + (i << 5));
    }
    s32 getQ(s32 k) {
        if (k < 0 || k >= unk90) return 0;
        return unk94[k];
    }
    s32 getQ(Obj00168740 *o) {
        return getQ(o->unk10);
    }
    s32 valid(s32 i) {
        if (i < 0 || i >= unkA0) return 0;
        return 1;
    }
};

typedef struct { u8 b[8]; } E8;
extern "C" {
void MtxMulVec4_13c900(Obj00168740 *, void *, void *);
void FrameCalcInvWorldMatrix_148fb0(s32, void *);
s32 VariantGetInt_15f780(E8 *);
extern Glob00168740 *D_00481154;
}

extern "C" Obj00168740 *DynFixVertexBindFrame_168740(E8 *arg0) {
    Mtx4 sp40;
    Vec4 sp30;
    s32 t;
    s32 idx;
    s32 q;
    Obj00168740 *p;

    t = VariantGetInt_15f780(arg0++);
    idx = VariantGetInt_15f780(arg0);
    p = D_00481154->getObj(idx);
    p->unk10 = t;
    if (p == 0) return 0;
    q = D_00481154->getQ(p->unk10);
    if (q == 0 || !D_00481154->valid(idx)) {
        p->unk10 = -1;
        return 0;
    }
    if (D_00481154->valid(idx)) {
        *(u128 *)&sp30 = *(u128 *)(D_00481154->unkA4 + idx * 0x10);
    }
    sp30.w = 1.0f;
    FrameCalcInvWorldMatrix_148fb0(q, &sp40);
    MtxMulVec4_13c900(p, &sp40, &sp30);
    p->unkC = 1.0f;
    p->unk14 = 1.0f;
    p->unk18 = 0;
    p->unk1C = 1.0f;
    return p;
}
