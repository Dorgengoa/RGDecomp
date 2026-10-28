/* rgp:protos */
#define RGP_SELF_TaskAddEncountDist_1f6d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x18E];
    s16 unk18E;
} Sub18_001F6D90;

typedef struct {
    u8 pad0[0x18];
    Sub18_001F6D90 *unk18;
    u8 pad1C[4];
    s32 unk20;
} Ctx001F6D90;

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
/*rgp*/
/*rgp*/
extern u8 D_004B8680[0x400];

void TaskAddEncountDist_1f6d90(void)
{
    u8 a[0x10] __attribute__((aligned(16)));
    u8 b[0x10] __attribute__((aligned(16)));
    Ctx001F6D90 *ctx;
    u8 *tbl;
    s32 i;
    s32 e;
    s32 cur;
    if (((unsigned char)FieldMapGetUpdateFlagRelated_201a50()) != 0) {
        return;
    }
    ctx = ((Ctx001F6D90 *)GetGameData_1fede0());
    tbl = D_004B8680;
    cur = ctx->unk18->unk18E;
    for (i = 0; i <= 11; i++) {
        e = ((s32)ActionMgrFindById_233b50(tbl, i));
        if (e != 0 && ((short)CharaGetActionMode_213850(e)) == 7) {
            return;
        }
    }
    e = ((s32)ActionMgrFindById_233b50(tbl, cur));
    if (e == 0) {
        return;
    }
    if (CharaIsFreeToActMaybe_2100a0(e) == 0) {
        return;
    }
    if (CharaEvObjContactFlag1Related_214920(e) != 0) {
        return;
    }
    if (CharaEvObjContactFlag2Related_2148e0(e) != 0) {
        return;
    }
    CharaGetPos_2388d0(e, a);
    if (MapSlotsIsPointFreeMaybe_1e3730(((s32)GetMapMgr_201a90()), a, 0.0f) == 0) {
        return;
    }
    if (EventObjMgrDoorsLiftsIdle_2e8c60(((s32)GetEventObjMgr_2d1960())) == 0) {
        return;
    }
    SrtGetPosThunk_1c7430(e, b);
    CharaSysEncounterDistTick_3a5890(ctx->unk20, VecDistXZ_1cb3f0(a, b));
}
