#pragma optimization_level 3
#pragma opt_propagation off
#include "types.h"
#include "vec.h"


/* Phase driver of the SetGameModePhase_1f59a0 family.  Outer chain is 0x3E8, 0x65,
   0x64, 4, 3, 2, 1, 0, -1, so the source order is -1, 0, 1, 2, 3, 4, 100,
   101, 1000; cases -1 and 0 share `D_0048226C = 0` and FALL THROUGH into
   case 1.  The inner switch on the s16 from InsectMenuGetStateThunk_397ec0 tests 1, 2,
   0, so its source order is 0, 2, 1.

   ★ D_0045B080 takes %hi/%lo and D_0047D1FC takes %gp_rel, from the same
   compiler on the same day: any <=4-byte extern is small-data unless its
   type has no size, so the first is declared as an INCOMPLETE ARRAY and
   indexed [0].  See memory/levers.d/main-phase-driver-family.md. */

struct S3 {
    u8 pad0[3];
    s8 m3;
};

struct R10 {
    u8 pad0[0x10];
    struct S3 *m10;
};

struct Q {
    s32 m0;
    struct R10 *m4;
};

struct Sub18 {
    u8  pad0[0x18E];
    s16 m18E;
};

struct Root {
    u8 pad0[0x18];
    struct Sub18 *m18;
};

extern const char D_004600B8[];
extern const char D_004600F8[];
extern const char D_004602D8[];
extern const char D_00460368[];
extern const char D_00460490[];
extern const char D_00460850[];
extern const char D_00460B50[];

extern f32 D_0045B080[];
extern f32 D_0047D1FC;
extern s32 D_00482264;
extern u8  D_00482268;
extern u8  D_0048226C;

extern void VecScaleToLength_1cb510(Vec4 *, Vec4 *, f32);
extern void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
extern f32  AngleWrap_1cbf30(f32);
extern void ClearGameReqHold_1f5880(void);
extern void SetGameReqHold_1f5890(void);
extern void SetGameModePhase_1f59a0(s32);
extern s32  GetGameModePhase_1f59b0(void);
extern void GameReqQueueRemoveById_1f5a10(s32);
extern void GameReqQueuePushBack_1f5b50(s32, s32);
extern s32  GetCurrentScene_1f5be0(void);
extern s32  GetInsectCageMgr_1fdb30(void);
extern s32  GetActionMgr_1fdb50(void);
extern struct Root *GetGameData_1fede0(void);
extern s32  GetMapMgr_201a90(void);
extern void InsectMenuCloseWithData_203100(void);
extern s32  InsectMenuResReady_2031b0(void);
extern void InsectMenuOpenWithData_2031d0(s32);
extern struct Q *GetSelectedInsectEntryMaybe_206ad0(void);
extern s32  ActionMgrFindById_233b50(s32, s16);
extern void CharaGetForwardVec_238830(s32, Vec4 *);
extern void CharaGetPos_2388a0(s32, Vec4 *);
extern void CharaGetRot_2388b0(s32, Vec4 *);
extern void TaskStatePushAll_27c220(void);
extern void TaskStatePopAll_27c250(void);
extern void TaskSetEnabled_27c2a0(s32, const char *);
extern s16  InsectMenuGetStateThunk_397ec0(void);
extern s32  CagePlaceCursorIsActive_39af20(s32);
extern void CagePlaceCursorEnd_39af30(s32);
extern void CagePlaceCursorSet_39af40(s32, s8, Vec4 *, Vec4 *);
extern void CagePlaceCursorSetFromSlot_39afb0(s32, s8);

s32 InsectMenuModeUpdate_27e610(void)
{
    struct Root *root;
    Vec4 pos;
    Vec4 scl;
    Vec4 rot;
    struct Q *q;
    struct R10 *r;
    s32 world;
    s32 hnd;
    s32 obj;

    root = GetGameData_1fede0();
    GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    world = GetActionMgr_1fdb50();
    hnd = GetInsectCageMgr_1fdb30();
    GameReqQueueRemoveById_1f5a10(0xE);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
    case 0:
        D_0048226C = 0;
    case 1:
        SetGameReqHold_1f5890();
        InsectMenuOpenWithData_2031d0(0);
        SetGameModePhase_1f59a0(0x3E8);
        {
            u8 one = 1;
            s16 id = root->m18->m18E;
            D_00482268 = one;
            obj = ActionMgrFindById_233b50(world, id);
        }
        if (obj == 0) {
            return 1;
        }
        q = GetSelectedInsectEntryMaybe_206ad0();
        if (q == 0) {
            goto fail1;
        }
        r = q->m4;
        if (r == 0) {
        fail1:
            return 1;
        }
        if (D_0048226C != 0) {
            CagePlaceCursorSetFromSlot_39afb0(hnd, r->m10->m3);
        } else {
            CharaGetPos_2388a0(obj, &pos);
            CharaGetRot_2388b0(obj, &rot);
            CharaGetForwardVec_238830(obj, &scl);
            { u32 s_ = (u32)&scl; VecScaleToLength_1cb510((Vec4 *)s_, (Vec4 *)s_, D_0045B080[0]); }
            { u32 p_ = (u32)&pos; VecAdd_1cbdc0((Vec4 *)p_, (Vec4 *)p_, &scl); }
            rot.y = AngleWrap_1cbf30(D_0047D1FC + rot.y);
            CagePlaceCursorSet_39af40(hnd, q->m4->m10->m3, &pos, &rot);
        }
        SetGameModePhase_1f59a0(3);
        return 1;
    case 2:
        SetGameReqHold_1f5890();
        InsectMenuOpenWithData_2031d0(1);
        SetGameModePhase_1f59a0(3);
        D_00482268 = 0;
        CagePlaceCursorEnd_39af30(hnd);
        return 1;
    case 3:
        GameReqQueueRemoveById_1f5a10(0x11);
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        q = GetSelectedInsectEntryMaybe_206ad0();
        if (q == 0 || q->m4 == 0) {
            SetGameModePhase_1f59a0(0x3E8);
            return 1;
        }
        TaskSetEnabled_27c2a0(0, D_004600B8);
        TaskSetEnabled_27c2a0(0, D_004600F8);
        TaskSetEnabled_27c2a0(0, D_00460368);
        TaskSetEnabled_27c2a0(0, D_00460850);
        TaskSetEnabled_27c2a0(0, D_004602D8);
        TaskSetEnabled_27c2a0(1, D_00460490);
        TaskSetEnabled_27c2a0(1, D_00460B50);
        SetGameModePhase_1f59a0(4);
        return 0;
    case 4:
        if (InsectMenuResReady_2031b0() == 0) {
            return 0;
        }
        D_00482264 = 0;
        if (D_00482268 != 0) {
            SetGameModePhase_1f59a0(0x65);
        } else {
            SetGameModePhase_1f59a0(0x64);
        }
        return 1;
    case 100:
        switch (InsectMenuGetStateThunk_397ec0()) {
        case 0:
            goto c0;
        case 2:
            InsectMenuCloseWithData_203100();
            D_0048226C = 1;
            SetGameModePhase_1f59a0(1);
            return 1;
        case 1:
            goto r0;
        }
    r0:
        return 0;
    c0:
        SetGameModePhase_1f59a0(0x3E8);
        return 1;
    case 101:
        if (CagePlaceCursorIsActive_39af20(hnd) != 0) {
            return 0;
        }
        SetGameModePhase_1f59a0(0x3E8);
        return 1;
    case 1000:
        InsectMenuCloseWithData_203100();
        q = GetSelectedInsectEntryMaybe_206ad0();
        q->m0 = -1;
        q->m4 = 0;
        CagePlaceCursorEnd_39af30(hnd);
        TaskStatePopAll_27c250();
        GameReqQueuePushBack_1f5b50(0, -1);
        ClearGameReqHold_1f5880();
        return 0;
    }
    return 0;
}
