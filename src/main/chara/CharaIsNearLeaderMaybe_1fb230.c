#include "types.h"

typedef struct S001fb230_Inner {
    u8 pad0[0x18E];
    s16 unk18E;
} S001fb230_Inner;

typedef struct S001fb230_Ctx {
    u8 pad0[0x18];
    S001fb230_Inner *unk18;
} S001fb230_Ctx;

extern s32 DoubleGreater_100260(s64 arg0, s64 arg1);
extern s64 dpmul(s64 arg0, s64 arg1);
extern f32 VecDistSqXZ_1cb390(void *arg0, void *arg1);
extern s32 MapSlotsFindById_1e4b90(s32 arg0, s32 arg1, s32 arg2);
extern s32 MapDataIsLoaded_1e79d0(s32 arg0);
extern S001fb230_Ctx *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 CharaCanFollowLeaderMaybe_20ffc0(s32 arg0);
extern s32 CharaGetAreaId_213c90(s32 arg0);
extern s32 ActionMgrFindById_233b50(void *arg0, s32 arg1);
extern void CharaGetPos_2388a0(s32 arg0, void *arg1);
extern s32 IsInBattle_288420(void);
extern s64 fptodp(f32 arg0);
extern f32 D_0045B080[0x100];
extern u8 D_004B8680[0x400];

s32 CharaIsNearLeaderMaybe_1fb230(s32 arg0, s32 arg1)
{
    u8 sp60[0x10];
    u8 sp50[0x10];
    s64 t;
    s64 d;
    u8 *tbl;
    s32 a;
    s32 b;
    S001fb230_Ctx *ctx;
    s32 w;

    tbl = D_004B8680;
    a = ActionMgrFindById_233b50(tbl, arg0);
    if (a == 0) {
        return 1;
    }
    ctx = GetGameData_1fede0();
    if (arg1 < 0) {
        arg1 = ctx->unk18->unk18E;
    }
    if (CharaCanFollowLeaderMaybe_20ffc0(a) == 0) {
        return 0;
    }
    w = GetMapMgr_201a90();
    w = MapSlotsFindById_1e4b90(w, CharaGetAreaId_213c90(a), 0);
    if (w == 0) {
        return 0;
    }
    if (MapDataIsLoaded_1e79d0(w) == 0) {
        return 0;
    }
    if (IsInBattle_288420() == 0) {
        b = ActionMgrFindById_233b50(tbl, arg1);
        if (b != 0) {
            CharaGetPos_2388a0(a, sp60);
            CharaGetPos_2388a0(b, sp50);
            t = dpmul((s64)0x403E0000 << 0x20, fptodp(D_0045B080[0]));
            d = fptodp(VecDistSqXZ_1cb390(sp60, sp50));
            if (DoubleGreater_100260(d, dpmul(t, t)) != 0) {
                return 0;
            }
        }
    }
    return 1;
}
