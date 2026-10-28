#include "types.h"

struct Rec {
    u8 pad0[2];
    s16 x2;
    s16 x4;
    u8 pad6[2];
    s32 x8;
};

struct VObj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Rec * Find(s16 a0) { return VCM(Rec *, (void *, s16), 0x70, a0); }
};

struct Sub38 {
    u8 pad0[8];
    VObj *x8;
};

struct G64 {
    u8 pad0[0x38];
    Sub38 *x38;
};

struct Lim {
    u8 pad0[6];
    s16 x6;
    u8 pad8[2];
    s16 xA;
};

struct G60 {
    u8 pad0[0x10];
    s32 x10;
    u8 pad14[4];
    Lim *x18;
    u8 pad1C[4];
    s32 x20;
};

extern "C" {
s32 GameReqPushWarp_285ea0(s32, s32, s32, s32);
void VariantSetS32_36f040(s32, s32, s32);
s32 VariantGetS32_36fb30(u8 *);
void CharaSysStatusClearAllActors_3a1de0(s32, s32, s32, s32);
s32 StateFlagTest_3ccd70(s32, s32);
}
extern "C" G60 *D_00483960;
extern "C" G64 *D_00483964;
extern "C" s32 D_00483968;
extern "C" s8 D_0048396C;

static inline s32 fix(s32 v)
{
    if (v > 0) {
        return v;
    }
    if (v == -2) {
        return D_00483960->x18->x6;
    }
    return D_00483960->x18->xA;
}

extern "C" void ScriptFnTransporterWarp_3d8e00(s32 arg0, s32 arg1, s32 arg2, u8 *arg3)
{
    s32 id;
    s32 sel;
    s32 lim;
    s32 extra;
    s32 flag;
    s32 key;
    Rec *r;
    u8 res;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    key = VariantGetS32_36fb30(arg3);
    id = -1;
    flag = 0;
    extra = 0;
    sel = id;
    lim = id;
    if (arg2 >= 2) {
        arg3 += 0x38;
        flag = VariantGetS32_36fb30(arg3) != 0;
    }
    if (arg2 >= 3) {
        arg3 += 0x38;
        lim = VariantGetS32_36fb30(arg3);
    }
    if (lim <= 0) {
        if (lim == -2) {
            lim = D_00483960->x18->x6;
        } else {
            lim = D_00483960->x18->xA;
        }
    }
    if (arg2 >= 4) {
        extra = VariantGetS32_36fb30(arg3 + 0x38);
        if (extra < 0) {
            extra = 0;
        }
    }
    if (flag != 0) {
        sel = key;
    } else {
        id = key;
        r = D_00483964->x38->x8->Find(key);
        if (r != 0) {
            sel = r->x8;
            lim = fix(r->x2);
            if (arg2 < 4) {
                if (r->x4 >= 0) {
                    extra = r->x4;
                }
            }
        }
    }
    if (sel < 0 || lim < 0) {
        return;
    }
    res = GameReqPushWarp_285ea0(id, sel, lim, extra);
    D_0048396C = 1;
    if (id >= 0 && StateFlagTest_3ccd70(D_00483960->x10, 0x7F1) == 0) {
        CharaSysStatusClearAllActors_3a1de0(D_00483960->x20, 0, 0, 0);
    }
    VariantSetS32_36f040(arg0, res, 1);
}
