#include "types.h"
#pragma opt_propagation off

class Obj003d3ef0 {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual s32 vB4();
    u8 pad4[0xC];
    s32 unk10;
};

typedef struct {
    u8 pad0[0x6];
    u16 unk6;
} Obj0040e110;

typedef struct {
    u8 pad0[0x94];
    f32 unk94;
    f32 unk98;
} Obj3d3ef0_b;

extern "C" Obj0040e110 *ItemDefGetWeaponData_40e110(s32);
extern "C" s32 D_00465BF8[];
extern "C" u8 *D_004838EC;
extern "C" f32 D_0047D258;

extern "C" s32 ItemWeaponGetPowerMaybe_3d3ef0(Obj003d3ef0 *arg0)
{
    s32 v;
    Obj0040e110 *t;
    Obj3d3ef0_b *b;
    f32 fv;
    f32 x;
    f32 y;
    f32 k;

    t = ItemDefGetWeaponData_40e110(arg0->unk10);
    if (t == NULL) {
        return 0;
    }
    v = t->unk6 & 0x3FF;
    if (arg0->vB4() != 0) {
        b = *(Obj3d3ef0_b **)(*(u8 **)(D_004838EC + 0x40) + 0x8);
        x = b->unk94; y = b->unk98; fv = (f32)v;
        v = (s32)(D_0047D258 + (y + fv * x));
    }
    if (D_00465BF8[0] < v) {
        v = D_00465BF8[0];
    }
    return v;
}
