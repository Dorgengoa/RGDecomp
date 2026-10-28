#include "types.h"
#include "vec.h"

struct Elem {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
};

struct Mgr {
    u8 pad0[0xA0];
    s32 nA0;
    Vec4 *pA4;
    u8 padA8[0xD4 - 0xA8];
    s32 nD4;
    Elem *pD8;

    Elem *GetElem(s32 i) {
        if (i < 0 || i >= nD4) {
            return 0;
        }
        return &pD8[i];
    }
    int Valid(s32 i) {
        if (i < 0 || i >= nA0) {
            return 0;
        }
        return 1;
    }
};

extern "C" {
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
f32 VariantGetFloat_15f740(s32);
s32 VariantGetInt_15f780(s32);
}
extern "C" Mgr *D_00481154;
extern "C" s32 D_0048116C;
extern "C" s32 D_00481178;

extern "C" s32 DynBindVertexCmd_167cd0(s64 *arg0, s32 arg1)
{
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Elem *e;
    s32 i0;
    s32 i1;

    e = D_00481154->GetElem(D_0048116C++);
    if (e == 0) {
        return 0;
    }
    i0 = D_00481178 + VariantGetInt_15f780((s32)arg0++);
    i1 = D_00481178 + VariantGetInt_15f780((s32)arg0++);
    if (!D_00481154->Valid(i0) || !D_00481154->Valid(i1)) {
        return 0;
    }
    e->unk8 = 0.5f;
    if (arg1 >= 3) {
        f32 f = VariantGetFloat_15f740((s32)arg0++);
        e->unk8 = f;
        if (!(f <= 1.0f) || f < 0.0f) {
            e->unk8 = 0.5f;
        }
    }
    e->unk0 = i0;
    e->unk4 = i1;
    if (D_00481154->Valid(i0)) {
        a = D_00481154->pA4[i0];
    }
    if (D_00481154->Valid(i1)) {
        b = D_00481154->pA4[i1];
    }
    e->unkC = VecDistance_13d3d0(&a, &b);
    if (arg1 >= 4) {
        e->unkC = e->unkC * VariantGetFloat_15f740((s32)arg0);
    }
    return 1;
}
