/* rgp:protos */
#line 1
#include "types.h"

class C371A70 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v50() { VCM0(void, 0xD0); }
    
    
    
    
    
    
    
    
    
    void v60() { VCM0(void, 0xF8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f101(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f114(s32 a0) { return VCM(s32, (void *, s32), 0x1D0, a0); }
};

extern "C" {
extern f32 GetScaledGravity_23b170(void);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
extern void MatIdentity_1cbe40(void *);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern u8 *GetActionMgr_1fdb50(void);
extern u8 *GetGameData_1fede0(void);
extern s32 CharaHasEvObjContact_214960(u8 *);
extern u8 *CharaGetEvObjContact_214990(u8 *);
extern u8 *ActionMgrFindById_233b50(u8 *, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetPos_2e0bb0(s32, void *, void *);
extern void EffectCreateByName_2e1020(void *, s32, void *, s32);
extern f32 EventParamRecGetLimit_2e3af0(s32);
extern f32 EventParamRecGetDamping_2e3b00(s32);
extern f32 EventParamRecGetSpring_2e3b10(s32);
extern f32 EventVolumeRecGetMass_2e4d20(s32);
extern void TargetRefResolve_2e5ed0(void *, s32);
extern void TargetRefApplyToEventObj_2e6810(void *, void *);
extern void TargetRefGetPos_2e6a60(void *, f32 *);
extern s32 TargetRefGetId_2e7120(void *);
extern s32 TargetRefGetKind_2e7130(void *);
extern void EventObjSetFromMatrix_2e72f0(void *, void *);
extern void EventObjGetPos_2e7640(void *, f32 *);
extern void EvObjUpdateBase_2f9910(u8 *);
extern s32 ObjTypeMonographIsActiveWithRecs_372be0(u8 *, int, int, int);
extern C371A70 *ActorFindById_3eb870(u8 *, s32);
extern f32 D_0045B080[];
extern u8 D_00463810[];
}

static inline bool Not31(u8 *o) {
    return !((*(u32 *)(o + 0xD0) & 0x80000000) != 0);
}

static inline bool Not29(u8 *o) {
    return !((*(u32 *)(o + 0xD0) & 0x20000000) != 0);
}

extern "C" void ObjTypeMonographUpdate_371a70(u8 *o, u8 *p) {
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(f32[12])) + (0x30 + sizeof(f32[4])) + (0x40)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(f32[12]) <= (0x30) && (0x0) >= 0 ? 1 : -1];
    
    u8 v60[0x20] __attribute__((aligned(16)));
    f32 v50[4] __attribute__((aligned(16)));
    f32 t;
    f32 f20;
    s32 s;
    f32 f21;
    f32 g;
    f32 f4;
    f32 lim;
    f32 a;
    C371A70 *c;
    u8 *q;
    s32 n;

    EvObjUpdateBase_2f9910(o);
    t = *(f32 *)(o + 0xF8) - *(f32 *)p;
    *(f32 *)(o + 0xF8) = t;
    if (t < 0.0f) {
        *(f32 *)(o + 0xF8) = -1.0f;
    }
    *(u32 *)(o + 0xD0) &= ~0x200000;
    if (!Not31(o)) {
        *(u32 *)(o + 0xD0) |= 0x1000000;
        return;
    }
    TargetRefApplyToEventObj_2e6810(o + 0xA0, o + 0x10);
    f20 = *(f32 *)(o + 0x100);
    t = f20 - *(f32 *)p;
    *(f32 *)(o + 0x100) = t;
    if (t < 0.0f) {
        *(f32 *)(o + 0x100) = -1.0f;
    }
    if (!(*(f32 *)(o + 0x100) < 0.0f)) {
        return;
    }
    TargetRefResolve_2e5ed0(o + 0xA0, 0);
    if (ObjTypeMonographIsActiveWithRecs_372be0(o, 0, 0, 0) == 0) {
        *(u32 *)(o + 0xD0) |= 0x1000000;
        return;
    }
    if (!(*(f32 *)(o + 0x104) < 0.0f)) {
        t = *(f32 *)(o + 0x104) + *(f32 *)p;
        *(f32 *)(o + 0x104) = t;
        if (!(t <= 40.0f)) {
            *(f32 *)(o + 0x104) = -1.0f;
        }
    }
    *(u32 *)(o + 0xD0) &= ~0x40000000;
    MatIdentity_1cbe40((*(f32 (*)[12])(rgp_blk1 + 0x0)));
    TargetRefGetPos_2e6a60(o + 0xA0, (*(f32 (*)[4])(rgp_blk1 + 0x30)));
    (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] = (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] + *(f32 *)(o + 0xF0);
    if (GetGameMode_1f59c0() != 11 && GetGameMode_1f59c0() != 9 && !(f20 < 0.0f)) {
        s = GetEffectMgr_2d9040();
        EffectCreateByName_2e1020(v60, s, D_00463810, -1);
        EffectSetPos_2e0bb0(s, v60, (*(f32 (*)[4])(rgp_blk1 + 0x30)));
        SoundPlayScaledVolume_1b9520(GameSceneSoundSlot5GetHandle_1d0790(GetCurrentScene_1f5be0()), 0x50, 0, 1.0f);
    }
    if (!Not29(o)) {
        EventObjSetFromMatrix_2e72f0(o + 0x10, (*(f32 (*)[12])(rgp_blk1 + 0x0)));
        *(f32 *)(o + 0xE8) = 0.0f;
        *(f32 *)(o + 0xEC) = 0.0f;
        return;
    }
    *(f32 *)(o + 0xE8) = *(f32 *)(o + 0xE8) * (1.0f - EventParamRecGetDamping_2e3b00(*(s32 *)(o + 0xE4)));
    EventObjGetPos_2e7640(o + 0x58, v50);
    f20 = ((*(f32 (*)[4])(rgp_blk1 + 0x30))[1] - v50[1]) * EventParamRecGetSpring_2e3b10(*(s32 *)(o + 0xE4)) + *(f32 *)(o + 0xEC) * GetScaledGravity_23b170();
    f4 = f20 / EventVolumeRecGetMass_2e4d20(*(s32 *)(o + 0xE0));
    t = *(f32 *)(o + 0xE8) + f4;
    lim = 0.25f * D_0045B080[0];
    *(f32 *)(o + 0xE8) = t;
    a = t;
    if (t < 0.0f) {
        a = -t;
    }
    if (!(a <= lim)) {
        if (*(f32 *)(o + 0xE8) < 0.0f) {
            *(f32 *)(o + 0xE8) = -lim;
        } else {
            *(f32 *)(o + 0xE8) = lim;
        }
    }
    v50[1] = v50[1] + *(f32 *)(o + 0xE8);
    f21 = (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] - v50[1];
    if (f21 < 0.0f) {
        f20 = -f21;
    } else {
        f20 = f21;
    }
    if (!(f20 <= EventParamRecGetLimit_2e3af0(*(s32 *)(o + 0xE4)))) {
        if (f21 < 0.0f) {
            (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] = (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] + EventParamRecGetLimit_2e3af0(*(s32 *)(o + 0xE4));
        } else {
            (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] = (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] - EventParamRecGetLimit_2e3af0(*(s32 *)(o + 0xE4));
        }
    } else {
        (*(f32 (*)[4])(rgp_blk1 + 0x30))[1] = v50[1];
    }
    *(f32 *)(o + 0xEC) = 0.0f;
    EventObjSetFromMatrix_2e72f0(o + 0x10, (*(f32 (*)[12])(rgp_blk1 + 0x0)));
    if (((short)TargetRefGetKind_2e7130(o + 0xA0)) == 5) {
        s = GetCurrentScene_1f5be0();
        if (ObjRecGetFlags_1c3d90(s, 1, ((short)TargetRefGetId_2e7120(o + 0xA0))) & 0x10000000) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
        c = ActorFindById_3eb870(GetGameData_1fede0(), ((short)TargetRefGetId_2e7120(o + 0xA0)));
        if (c == 0 || c->f101(0x1F) == 0 || c->f114(0x1F) <= 0) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
        q = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), ((short)TargetRefGetId_2e7120(o + 0xA0)));
        if (q != 0 && CharaHasEvObjContact_214960(q) != 0 && *(s16 *)(CharaGetEvObjContact_214990(q) + 4) == 3) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
    }
    if ((*(u32 *)(o + 0xD0) & 0x800000) && *(u8 *)(p + 4) == 0) {
        t = *(f32 *)(o + 0xFC) - *(f32 *)p;
        *(f32 *)(o + 0xFC) = t;
        n = (s32)t;
        if (t < 90.0f) {
            *(u32 *)(o + 0xD0) = ((n >> 1) & 1) ? (*(u32 *)(o + 0xD0) | 0x200000) : (*(u32 *)(o + 0xD0) & ~0x200000);
        } else if (t < 300.0f) {
            *(u32 *)(o + 0xD0) = ((n >> 2) & 1) ? (*(u32 *)(o + 0xD0) | 0x200000) : (*(u32 *)(o + 0xD0) & ~0x200000);
        }
        if (*(f32 *)(o + 0xFC) < 0.0f) {
            *(u32 *)(o + 0xD0) |= 0x1000000;
        }
    }
}
