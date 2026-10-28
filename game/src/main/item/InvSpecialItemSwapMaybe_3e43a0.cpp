#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct Obj Obj;
typedef struct {
    u8 pad0[0x60];
    s32 (*unk60)(Obj *);
    u8 pad64[0x90 - 0x64];
    s32 (*unk90)(Obj *, s32);
    u8 pad94[0xAC - 0x94];
    s32 (*unkAC)(Obj *);
} ObjVTab;
struct Obj {
    ObjVTab *unk0;
    u8 pad4[0x6 - 0x4];
    s16 unk6;
    u8 pad8[0x10 - 0x8];
    s16 *unk10;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad0[0x398];
    s32 (*unk398)(Handle **, s32);
};

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
    s32 unk18;
} Ctx;

extern Obj *InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern s32 InvDiscardItem_3c5010(s32, Obj *, s32);
extern s32 InvAddItemAtSlot_3c64c0(s32, s32, s32, s32, s32);
extern s32 InvAddItemCoreMaybe_3c6540(s32, s32, s32, s32, s32, s32, s32);
extern void InvPurgeRemoved_3c8cc0(s32);
extern Handle **CharaMgrPoolFindById_3a8c60(s32, s32);
extern s16 D_004801F8;
extern s8 D_004839D8;
extern s8 D_004839DC;
extern s8 D_004839E0[5];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x60); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xAC); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x90, x0); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x398, x0); }
};
s32 InvSpecialItemSwapMaybe_3e43a0(Ctx *arg0) {
    Obj *var_18;
    u32 var_17;
    s32 var_2;
    Handle **temp_2_2;
    s32 var_16;

    if ((var_18 = InvFindInCategoryRange_3c8370(arg0->unk18, 0x3ED7, 0, -1, 0, 0)) == NULL) {
        var_18 = InvFindInCategoryRange_3c8370(arg0->unk18, 0x3ED8, 0, -1, 0, 0);
    }
    if (var_18 == NULL) {
        var_18 = InvFindInCategoryRange_3c8370(arg0->unk18, 0x3ED9, 0, -1, 0, 0);
    }
    if (var_18 == NULL) {
        var_18 = InvFindInCategoryRange_3c8370(arg0->unk18, 0x3EDA, 0, -1, 0, 0);
    }
    var_17 = -1;
    if (var_18 != NULL) {
        var_17 = var_18->unk6;
        D_004801F8 = *var_18->unk10;
        D_004839DC = ((VC_0 *)(var_18))->f();
        D_004839D8 = ((VC_1 *)(var_18))->f();
        var_16 = 0;
        do {
            D_004839E0[var_16] = ((VC_2 *)(var_18))->f(var_16);
            var_16 += 1;
        } while (var_16 < 5);
        InvDiscardItem_3c5010(arg0->unk18, var_18, 1);
    }
    InvPurgeRemoved_3c8cc0(arg0->unk18);
    if (var_18 != NULL) {
        var_2 = InvAddItemAtSlot_3c64c0(arg0->unk18, 0x4110, var_17, 1, 0);
    } else {
        var_2 = InvAddItemCoreMaybe_3c6540(arg0->unk18, 0x4110, 0, 1, -1, 0, 0);
    }
    if (var_2 == 0) {
        return 0;
    }
    temp_2_2 = CharaMgrPoolFindById_3a8c60(arg0->unk14, 0);
    ((VC_3 *)(temp_2_2))->f(var_2);
    return 1;
    return 0;
}

}
