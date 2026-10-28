/* rgp:protos */
#line 1
#include "types.h"

class ObjB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fC0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f1A8(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A8, a0, a1, a2); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f2BC(s32 a0, f32 a1) { VCM(void, (void *, s32, f32), 0x2BC, a0, a1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f47C() { VCM0(void, 0x47C); }
};

class SubB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f64(s32 a0) { VCM(void, (void *, s32), 0x64, a0); }
};

class Sub : public SubB {
public:
    u8 pad4[0x24];
};

typedef struct {
    u8 b0 : 1;
    u8 b1 : 7;
} Bits;

class Obj : public ObjB {
public:
    u8 pad4[0x1C0 - 4];
    Bits unk1C0;
    u8 pad1C1[3];
    f32 unk1C4;
    Bits unk1C8;
    u8 pad1C9[0x1D4 - 0x1C9];
    s16 unk1D4;
    s16 unk1D6;
    u8 pad1D8[0x308 - 0x1D8];
    Sub sub[10];
    u8 pad498[0x4A4 - 0x498];
    s32 unk4A4;
    s32 unk4A8;
    u8 unk4AC;
};

typedef struct {
    u8 pad0[0x24C];
    u8 b0 : 1;
} P20;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0xC];
    P20 *unk20;
} G;

extern "C" {
s32 CharaSysStateField28ValidRelated_3a3920(P20 *);
s32 StateFlagTest_3ccd70(s32, s32);
}
extern "C" s32 D_00465CD0[];
extern "C" G *D_00483818;

extern "C" s32 CharaOnBattleEnd_3aa840(Obj *arg0, s32 arg1)
{
    bool ok;
    s32 i;

    if (D_00483818 == NULL) {
        return 0;
    }
    if (!D_00483818->unk20->b0) {
        return 0;
    }
    arg0->unk4A8 += arg0->unk1D6;
    arg0->unk4A4 += arg0->unk1D4;
    ok = true;
    if (((unsigned char)CharaSysStateField28ValidRelated_3a3920(D_00483818->unk20)) != 0 && StateFlagTest_3ccd70(D_00483818->unk10, 0x7E6) != 0) {
        ok = false;
    }
    if (arg0->fC0() != 0) {
        arg0->unk4AC = 1;
        if (arg1 != 2 && ok) {
            arg0->f2BC(0, 0.0f);
        }
    }
    if (ok) {
        arg0->f1A8(1, 1, 1);
    }
    for (i = 0; i < 10; i++) {
        arg0->sub[i].f64(arg1);
    }
    arg0->unk1C4 = D_00465CD0[0];
    arg0->unk1C8.b0 = false;
    arg0->unk1C0.b0 = true;
    arg0->f47C();
    return 1;
}
