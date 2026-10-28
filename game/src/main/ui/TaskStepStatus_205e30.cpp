/* rgp:protos */
#line 1
#include "types.h"

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f274(s32 a0) { return VCM(s32, (void *, s32), 0x274, a0); }
};

class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f3C0() { return VCM0(s32, 0x3C0); }
};

extern "C" {
s32 ProjectToScreenOffset_15d160(s32 *, s32 *);
void ObjRecGetLiveObject_1c3bc0(u8 *, s32);
s32 ObjRecGetFlags_1c3d90(u8 *, s32, s32);
s32 ObjRecHasFlags6_1c3eb0(u8 *, s32, s32);
s32 ObjRecGetLiveObject_1c4a90(u8 *, s32);
s32 MapSlotsFindActiveBlockById_1e4730(s32, s32, s32);
s32 MapDataIsJasterOnly_1e7a90(s32);
s32 GetGameMode_1f59c0(void);
u8 *GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
u8 *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
s32 CharaCanActMaybe_210500(s32);
f32 CharaGaugeDrainFxGetAlphaMaybe_214220(s32);
s32 ActionMgrFindById_233b50(s32, s32);
s32 ObjGetNthAttachPointPosSafe_23b0c0(s32, s32, s32, s32 *);
s32 IsInBattle_288420(void);
u8 *NpcObjFindDefById_2fb490(s32, s32);
s32 GetNpcObjTable_312860(void);
void ScreenMarkerSetFlagById_31a900(u8 *, s32, s32);
void ScreenMarkerSetNearDist_31ae10(u8 *, f32);
void ScreenMarkerSetFarDist_31ae30(u8 *, f32);
void ScreenMarkerAdd_31ae50(u8 *, s32, s8);
void ScreenMarkerMgrUpdate_31bce0(u8 *);
void HpGaugeUpdate_31c2d0(u8 *);
void HpGaugeShow_31d2b0(u8 *, s32, f32);
void HpGaugeUpdateThin_31d3d0(u8 *);
VC_1 *ObjFindById_3bb3a0(s32, s32);
VC_0 *ActorFindById_3eb870(u8 *, s32);
extern f32 D_0047D288;
extern u8 D_004BC310[];
extern u8 D_004BC470[];
extern u8 D_004BC6C0[];
void TaskStepStatus_205e30(void);
}

static inline bool isOn(void) {
    return ((unsigned char)IsInBattle_288420()) != 0;
}

static inline bool isOff(void) {
    return !isOn();
}

void TaskStepStatus_205e30(void) {
    s32 pos[4] __attribute__((aligned(16)));
    s32 rect[4] __attribute__((aligned(16)));
    u8 *sys;
    u8 *mgr;
    s32 tbl;
    s32 ctx;
    s32 sel;
    s32 r;
    bool ok;
    s32 i;
    bool hi;
    bool lock;
    s32 p;
    s32 u;
    VC_0 *q;
    VC_1 *w;
    u8 *e;


    switch (GetGameMode_1f59c0()) {
    case 6:
    case 11:
    case 12:
        ScreenMarkerSetFarDist_31ae30(D_004BC310, 320.0f);
        ScreenMarkerSetNearDist_31ae10(D_004BC310, 20.0f);
        break;
    case 7:
        ScreenMarkerSetFarDist_31ae30(D_004BC310, 1000.0f);
        ScreenMarkerSetNearDist_31ae10(D_004BC310, 20.0f);
        break;
    default:
        return;
    }
    sys = GetCurrentScene_1f5be0();
    mgr = GetGameData_1fede0();
    ObjRecGetLiveObject_1c3bc0(sys, *(s32 *)(sys + 0x4344));
    tbl = GetActionMgr_1fdb50();
    ctx = GetNpcObjTable_312860();
    r = GetMapMgr_201a90();
    sel = *(s16 *)(*(u8 **)(mgr + 0x18) + 0x18E);
    r = MapSlotsFindActiveBlockById_1e4730(r, *(s16 *)(*(u8 **)(mgr + 0x18) + 0x30), 0);
    ok = r != 0;
    lock = false;
    if (ok) {
        ok = ((unsigned char)MapDataIsJasterOnly_1e7a90(r)) != 0;
    }
    if (ok) {
        u32 m = (((unsigned char)IsInBattle_288420()) != 0) ^ 1;
        if (m) {
            lock = true;
        }
    }
    i = 0;
    do {
        hi = false;
        if (i >= 0 && i < 12) {
            if (lock) {
                ScreenMarkerSetFlagById_31a900(D_004BC310, 0, i);
                goto next;
            }
            p = ActionMgrFindById_233b50(tbl, i);
            if (p == 0) {
                goto next;
            }
            if (((unsigned char)IsInBattle_288420()) != 0) {
                if (CharaGaugeDrainFxGetAlphaMaybe_214220(p) < D_0047D288) {
                    goto next;
                }
                q = ActorFindById_3eb870(mgr, i);
                if (q == 0) {
                    goto next;
                }
                if (q->f274(-1) != 0) {
                    goto next;
                }
                HpGaugeShow_31d2b0(D_004BC6C0, i, 1.5f);
                goto next;
            }
            if (CharaCanActMaybe_210500(p) == 0) {
                goto next;
            }
        }
        if (i == sel) {
            goto next;
        }
        if (((unsigned char)ObjRecHasFlags6_1c3eb0(sys, 1, i)) == 0) {
            goto next;
        }
        if (ObjRecGetFlags_1c3d90(sys, 1, i) & 0x80000) {
            goto next;
        }
        u = ObjRecGetLiveObject_1c4a90(sys, i);
        if (u == 0) {
            goto next;
        }
        if (i >= 0x80 && i < 0x9C) {
            w = ObjFindById_3bb3a0(*(s32 *)(mgr + 0x1C), i);
            if (w == 0) {
                goto next;
            }
            if (((unsigned char)IsInBattle_288420()) == 0) {
                goto next;
            }
            if (w->f3C0() != 0) {
                goto next;
            }
        }
        if (i >= 0xC0 && i < 0xE0) {
            e = NpcObjFindDefById_2fb490(ctx, i);
            if (e == 0) {
                goto next;
            }
            hi = (*(s32 *)(e + 0x48) & 0x3E) != 0;
        }
        if (ObjGetNthAttachPointPosSafe_23b0c0(u, 0, 0, pos) == 0) {
            goto next;
        }
        if (ProjectToScreenOffset_15d160(rect, pos) == 0) {
            goto next;
        }
        ScreenMarkerAdd_31ae50(D_004BC310, i, hi);
    next:
        i++;
    } while (i < 0xE0);
    HpGaugeUpdateThin_31d3d0(D_004BC470);
    HpGaugeUpdate_31c2d0(D_004BC6C0);
    ScreenMarkerMgrUpdate_31bce0(D_004BC310);
}
