/* rgp:protos */
#define RGP_SELF_CharaIsNearLeaderMaybe_1fb230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S001fb230_Inner {
    u8 pad0[0x18E];
    s16 unk18E;
} S001fb230_Inner;

typedef struct S001fb230_Ctx {
    u8 pad0[0x18];
    S001fb230_Inner *unk18;
} S001fb230_Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[0x100];
extern u8 D_004B8680[0x400];

s32 CharaIsNearLeaderMaybe_1fb230(s32 arg0, s32 arg1)
{
    u8 sp60[0x10] __attribute__((aligned(16)));
    u8 sp50[0x10] __attribute__((aligned(16)));
    s64 t;
    s64 d;
    u8 *tbl;
    s32 a;
    s32 b;
    S001fb230_Ctx *ctx;
    s32 w;

    tbl = D_004B8680;
    a = ((s32)ActionMgrFindById_233b50(tbl, arg0));
    if (a == 0) {
        return 1;
    }
    ctx = ((S001fb230_Ctx *)GetGameData_1fede0());
    if (arg1 < 0) {
        arg1 = ctx->unk18->unk18E;
    }
    if (CharaCanFollowLeaderMaybe_20ffc0(a) == 0) {
        return 0;
    }
    w = ((s32)GetMapMgr_201a90());
    w = MapSlotsFindById_1e4b90(w, CharaGetAreaId_213c90(a), 0);
    if (w == 0) {
        return 0;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0(w)) == 0) {
        return 0;
    }
    if (((unsigned char)IsInBattle_288420()) == 0) {
        b = ((s32)ActionMgrFindById_233b50(tbl, arg1));
        if (b != 0) {
            CharaGetPos_2388a0(a, sp60);
            CharaGetPos_2388a0(b, sp50);
            t = ((s64)__builtin_bit_cast(long long, dpmul(__builtin_bit_cast(double, (long long)((s64)0x403E0000 << 0x20)), fptodp(D_0045B080[0]))));
            d = ((s64)__builtin_bit_cast(long long, fptodp(VecDistSqXZ_1cb390(sp60, sp50))));
            if (((unsigned char)DoubleGreater_100260(__builtin_bit_cast(double, (long long)(d)), dpmul(__builtin_bit_cast(double, (long long)(t)), __builtin_bit_cast(double, (long long)(t))))) != 0) {
                return 0;
            }
        }
    }
    return 1;
}
