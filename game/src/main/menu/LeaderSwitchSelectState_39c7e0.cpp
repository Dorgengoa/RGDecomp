/* rgp:protos */
#line 1
#include "types.h"

class Unit {
public:
    VC_VPTR_MEMBER;   
       
       
       
       
    
    s32 f5C() { return VCM0(s32, 0x5C); }
    u8 pad4[0x8];
    s32 id;
    u8 pad10[0x4B4 - 0x10];
    u8 flag4B4;
};

extern "C" {
extern s32 PadIsTriggered_1839f0(u8 *, s32);
extern s32 CharaIsNearLeaderMaybe_1fb230(s32, s32);
extern u8 *GetGameData_1fede0(void);
extern s32 MenuGridCursorInput_28e170(u8 *, u8 *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(u8 *, s32, s32);
extern u8 *UiEntryListGetCurrentData_28ec60(u8 *);
extern void StateMachineSetState_28ede0(u8 *, s32, s32);
extern void PartySwitchLeader_2f3ca0(s32, s32);
extern s32 CharaCanBeLeader_3ae200(Unit *, s32, int, int);
extern s32 PartyCountMembers_3c2010(u8 *, s32, s32);
extern Unit *PartyGetMemberChara_3c2420(u8 *, s32);
extern Unit *PartyGetLeaderChara_3c2820(u8 *);
extern u8 D_00483600;
extern s32 D_00483630;
extern s32 D_00483634;
extern u8 D_004B2570[];
extern u8 D_004E9630[];
}

extern "C" s32 LeaderSwitchSelectState_39c7e0(s32 pad0, s32 arg1)
{
    s32 k;
    s32 r;
    s32 i;
    u8 *sel;
    s16 *sp;
    Unit *self;
    u8 *ctx;
    Unit *u;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004E9630, 0x7149, 0);
        goto ret1;
    }
    r = MenuGridCursorInput_28e170(D_004E9630, D_004B2570, 4, 0);
    sel = UiEntryListGetCurrentData_28ec60(D_004E9630);
    if (r == 1) {
        ctx = GetGameData_1fede0();
        if (ctx == 0) {
            return 0;
        }
        {
            s16 tbl[3] = {0};
            k = 0;
            self = PartyGetLeaderChara_3c2820(*(u8 **)(ctx + 0x18));
            for (i = 0; i < PartyCountMembers_3c2010(*(u8 **)(ctx + 0x18), 1, 1); i++) {
                u = PartyGetMemberChara_3c2420(*(u8 **)(ctx + 0x18), i);
                if (self->f5C() == u->f5C()) {
                    continue;
                }
                sp = &tbl[k];
                *sp = u->id;
                if (CharaCanBeLeader_3ae200(u, 0, 0, 0) == 0) {
                    goto bad;
                }
                if (u->flag4B4 & 1) {
                    goto bad;
                }
                if (*(*(u8 **)(ctx + 0x18) + 0x42D0) & 1) {
                bad:
                    *sp = -1;
                } else if (CharaIsNearLeaderMaybe_1fb230(u->id, -1) == 0) {
                    *sp = 9999;
                }
                k++;
            }
            sp = &tbl[*(s16 *)(sel + 0x12)];
            if (*sp >= 0) {
                if (*sp == 9999) {
                    StateMachineSetState_28ede0(&D_00483600, 0x714C, 1);
                } else {
                    s32 v = tbl[(u32)*(s16 *)(sel + 0x12)];
                    D_00483630 = 0;
                    D_00483634 = v;
                    PartySwitchLeader_2f3ca0(v, 0);
                    StateMachineSetState_28ede0(&D_00483600, 0x714B, 1);
                }
            }
        }
    } else if (r == 2 || PadIsTriggered_1839f0(D_004B2570, 0x200) != 0) {
        StateMachineSetState_28ede0(&D_00483600, 0x714B, 1);
    }
ret1:
    return 1;
}
