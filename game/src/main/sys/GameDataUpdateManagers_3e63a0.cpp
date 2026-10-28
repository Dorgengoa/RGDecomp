/* rgp:protos */
#line 1
#include "types.h"

struct A3e63a0 {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
    u8 pad28[0xA];
    s16 h32;
    u8 pad34[0x24];
    s16 h58;
};

extern "C" {
s16 *SysGetModeMsg_1c39b0(void);
s32 GetGameMode_1f59c0(void);
void GameReqQueuePushBack_1f5b50(s32, s32);
void CharaSysUpdate_3a0c10(s32, f32);
void BattleEncounterStartById_3a4160(s32, long long, s32, int);
void CharaSysEncounterBindAndStartMaybe_3a5340(s32, s32, s32, int);
void CharaMgrPoolUpdate_3a8490(s32, f32);
void ObjMgrUpdate_3ba490(s32, f32);
void PartyUpdateMaybe_3bfb60(s32, f32);
void StateBlockUpdateNop_3cbab0(void);
void OptionsUpdateNop_3d5ec0(void);
void EventTriggerSysUpdateMaybe_3e02c0(f32);
void InsectTeamTableUpdateNop_42feb0(void);
}

extern "C" s32 GameDataUpdateManagers_3e63a0(A3e63a0 *a, f32 f)
{
    bool b2;
    bool b1;
    s32 r;
    s16 *p;

    if (a->w8 == 0) {
        return 0;
    }
    if (a->wC == 0) {
        return 0;
    }
    if (a->w10 == 0) {
        return 0;
    }
    if (a->w14 == 0) {
        return 0;
    }
    if (a->w18 == 0) {
        return 0;
    }
    if (a->w1C == 0) {
        return 0;
    }
    if (a->w20 == 0) {
        return 0;
    }
    if (a->w24 == 0) {
        return 0;
    }
    OptionsUpdateNop_3d5ec0();
    StateBlockUpdateNop_3cbab0();
    CharaMgrPoolUpdate_3a8490(a->w14, f);
    PartyUpdateMaybe_3bfb60(a->w18, f);
    ObjMgrUpdate_3ba490(a->w1C, f);
    CharaSysUpdate_3a0c10(a->w20, f);
    InsectTeamTableUpdateNop_42feb0();
    EventTriggerSysUpdateMaybe_3e02c0(f);
    if (a->h32 == 1 && a->h58 >= 0) {
        b2 = false;
        b1 = false;
        r = GetGameMode_1f59c0();
        if (r == 6) {
            b2 = true;
        }
        p = SysGetModeMsg_1c39b0();
        if (p != 0 && *p == 6) {
            b1 = true;
            if (r == 1) {
                b2 = b1;
            }
        }
        if (b2) {
            if (!b1) {
                BattleEncounterStartById_3a4160(a->w20, (long long)(a->h58), 0, 0);
                GameReqQueuePushBack_1f5b50(7, 2);
            } else {
                CharaSysEncounterBindAndStartMaybe_3a5340(a->w20, a->h58, 99999, 0);
            }
            a->h58 = -1;
        }
    }
    return 1;
}
