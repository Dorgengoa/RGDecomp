#include "types.h"

typedef struct Unit {
    u8 pad0[0xA44];
    u32 mA44;
} Unit;

typedef struct Mdl {
    u8 pad0[0x90];
    u8 m90;
} Mdl;

typedef struct Sub {
    u8 pad0[0x18E];
    s16 m18E;
} Sub;

typedef struct Ctx {
    u8 pad0[0x18];
    Sub *m18;
} Ctx;

s32 MapBlockGetLocationId_1e0070(s32);
s32 MapFindBlockAtPos_1e3a00(s32, s32 *, f32);
s32 CharaResFindById_1efba0(void *, s32);
s32 CharaResRecIsReady_1f4890(s32);
void GetCurrentScene_1f5be0(void);
Ctx *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
s32 CharaGetActionMode_213850(Unit *);
s32 CharaGetAi_214a10(Unit *);
void ActionMgrThinkAll_2325a0(void *);
Unit *ActionMgrFindById_233b50(void *, s32);
void CharaGetPos_2388a0(Unit *, s32 *);
void AiSetKeepDistanceMaybe_2c0ed0(s32, f32);
void AiSetRunDistance_2c0ee0(s32, f32);
void AiSetStopDistance_2c0ef0(s32, f32);
void AiSetApproachMarginMaybe_2c0f00(s32, f32);
s32 AiGetTargetCharaId_2c0fd0(s32);
void AiGetTargetPos_2c0ff0(s32, s32 *);
Mdl *AiGetNavPath_2c10a0(s32);
s32 AiGetTargetMode_2c10b0(s32);
s32 GetNavMgr_2d1950(void);
void NavPlanPathToGoal_30b100(s32, s32 *, s32, Mdl *);
s32 NavSetGoalPos_30bd80(s32, s32 *, s32);
extern s32 D_0047E4B0;
extern s32 D_00481A88;
extern s32 D_00481A8C;
extern u8 D_004B7960[];
extern u8 D_004B8680[];

void TaskCharaThink_1fa9c0(void) {
    Unit *w;
    s32 buf[4];
    u8 *units;
    s32 self;
    u8 *slots;
    s32 mgr;
    s32 found;
    s32 i;
    Ctx *ctx;
    s32 cam;
    Unit *u;
    s32 h;
    s32 f;
    Mdl *m;



    ctx = GetGameData_1fede0();
    units = D_004B8680;
    slots = D_004B7960;
    mgr = GetNavMgr_2d1950();
    cam = GetMapMgr_201a90();
    GetCurrentScene_1f5be0();
    self = ctx->m18->m18E;
    D_00481A8C++;
    if (D_00481A8C == 5) {
        found = -1;
        for (i = 0; i < 0xE0; i++) {
            if (i == self) {
                continue;
            }
            if (D_0047E4B0 < i) {
                h = CharaResFindById_1efba0(slots, i);
                if (h == 0) continue;
                if (CharaResRecIsReady_1f4890(h) == 0) continue;
                u = ActionMgrFindById_233b50(units, i);
                if (u == 0) continue;
                f = u->mA44;
                if (!(f & 0x1000000)) continue;
                if (f & 0x80000) continue;
                if (CharaGetActionMode_213850(u) == 0x12) continue;
                if (CharaGetActionMode_213850(u) == 0x11) continue;
                h = CharaGetAi_214a10(u);
                if (AiGetTargetMode_2c10b0(h) == 1 || AiGetTargetCharaId_2c0fd0(h) >= 0) {
                    found = i;
                    break;
                }
            }
        }
        if (found != D_0047E4B0) {
            D_0047E4B0 = found;
        } else {
            found = -1;
            for (i = 0; i < 0xE0; i++) {
                if (i == self) {
                    continue;
                }
                h = CharaResFindById_1efba0(slots, i);
                if (h == 0) continue;
                if (CharaResRecIsReady_1f4890(h) == 0) continue;
                u = ActionMgrFindById_233b50(units, i);
                if (u == 0) continue;
                f = u->mA44;
                if (!(f & 0x1000000)) continue;
                if (f & 0x80000) continue;
                if (CharaGetActionMode_213850(u) == 0x12) continue;
                if (CharaGetActionMode_213850(u) == 0x11) continue;
                h = CharaGetAi_214a10(u);
                if (AiGetTargetMode_2c10b0(h) == 1 || AiGetTargetCharaId_2c0fd0(h) >= 0) {
                    found = i;
                    break;
                }
            }
            D_0047E4B0 = found;
        }
        h = *(volatile s32 *)&D_0047E4B0;
        if (h >= 0) {
            u = ActionMgrFindById_233b50(units, h);
            if (u != 0) {
                AiGetTargetPos_2c0ff0(CharaGetAi_214a10(u), buf);
                h = MapFindBlockAtPos_1e3a00(cam, buf, 0.0f);
                if (h != 0) {
                    if (NavSetGoalPos_30bd80(mgr, buf, MapBlockGetLocationId_1e0070(h)) != 0) {
                        D_00481A88 = 1;
                    }
                }
            }
        }
    } else if (D_00481A8C == 6) {
        if (D_00481A88 != 0) {
            w = ActionMgrFindById_233b50(units, D_0047E4B0);
            if (w != 0) {
                h = CharaGetAi_214a10(w);
                AiSetApproachMarginMaybe_2c0f00(h, 28.0f);
                AiSetStopDistance_2c0ef0(h, 4.0f);
                AiSetRunDistance_2c0ee0(h, 24.0f);
                AiSetKeepDistanceMaybe_2c0ed0(h, 48.0f);
                h = (s32)AiGetNavPath_2c10a0(h);
                ((Mdl *)h)->m90 = 0;
                CharaGetPos_2388a0(w, buf);
                f = MapFindBlockAtPos_1e3a00(cam, buf, 0.0f);
                if (f != 0) {
                    NavPlanPathToGoal_30b100(mgr, buf, MapBlockGetLocationId_1e0070(f), (Mdl *)h);
                }
            }
        }
        D_00481A88 = 0;
        D_00481A8C = 0;
    }
    ActionMgrThinkAll_2325a0(units);
}
