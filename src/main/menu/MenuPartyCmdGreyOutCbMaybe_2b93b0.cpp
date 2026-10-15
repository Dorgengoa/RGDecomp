/* PARKED s17b: not attempted. Deep chained-struct-deref fn (12+ extern
   calls, several `?`-typed fields including a bitfield-like `& 1` test on
   temp_17->unk20->unk24C). High risk/time relative to lane budget. See
   build/b_drafts/MenuPartyCmdGreyOutCbMaybe_2b93b0.txt for the m2c draft. Not attempted. */
/* s49m: MATCH */
#include "types.h"

struct Flags234 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 rest : 5;
};

struct Unit {
    u8 pad0[0xC];
    s32 mC;
    u8 pad10[0x224];
    Flags234 f234;
    u8 pad235[0x27F];
    u8 f4B4;
};

struct Pos {
    s8 x;
    s8 y;
};

struct Self {
    u8 pad0[0x12];
    s16 m12;
};

extern "C" {
extern s32 D_00482370;
extern u16 D_004614C0[];
u8 *GetGameData_1fede0(void);
Pos *MenuGetCursorPos_29fae0(s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
Unit *PartyGetSlotChara_3c2fb0(s32, s32);
void MenuPartyCmdListHighlight_29c440(s32, s32, s32, s32);
s32 MenuGetOpenLeaderId_29acd0(void);
s32 CharaIsNearLeaderMaybe_1fb230(s32, s32);
void MenuPartyCmdRowDim_29c390(s32, s32, s16);
s32 CharaIsPartyMember_3ae110(Unit *);
s32 CharaIsPartyLeader_3ae1a0(Unit *);
s32 CharaCanBeLeader_3ae200(Unit *, s32);
s32 CharaCountAbilitiesFilteredMaybe_3add30(Unit *, s32, s32, s32);
}

extern "C" s32 MenuPartyCmdGreyOutCbMaybe_2b93b0(Self *self)
{
    u8 *g;
    s32 h;
    Unit *u;
    s32 m;
    s32 v;
    bool ok;
    s32 id;
    Pos *pos;

    g = GetGameData_1fede0();
    pos = MenuGetCursorPos_29fae0(D_00482370);
    u = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), pos->x + pos->y * PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1));
    id = D_004614C0[pos->y];
    MenuPartyCmdListHighlight_29c440(D_00482370, id, self->m12, 1);
    m = u->mC;
    v = MenuGetOpenLeaderId_29acd0();
    ok = true;
    if (!(*(*(u8 **)(g + 0x20) + 0x24C) & 1)) {
        if (CharaIsNearLeaderMaybe_1fb230(m, v) == 0) {
            ok = false;
        }
    }
    h = *(s32 *)(g + 0x18);
    if (PartyCountMembers_3c2010(h, 1, 1) + PartyCountReserve_3c1c20(h, 1, 1) == 1) {
        MenuPartyCmdRowDim_29c390(D_00482370, id, 0);
    }
    if (PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1) == 1) {
        if (CharaIsPartyMember_3ae110(u)) {
            MenuPartyCmdRowDim_29c390(D_00482370, id, 0);
        }
    }
    if (u->f234.b2) {
        MenuPartyCmdRowDim_29c390(D_00482370, id, 0);
    }
    if (pos->y == 0) {
        if (CharaIsPartyLeader_3ae1a0(u) || !CharaCanBeLeader_3ae200(u, 0) || (u->f4B4 & 1) || !CharaIsPartyMember_3ae110(u) ||
            (*(*(u8 **)(g + 0x18) + 0x42D0) & 1) || !ok) {
            MenuPartyCmdRowDim_29c390(D_00482370, id, 1);
        }
        if (PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1) == 1) {
            MenuPartyCmdRowDim_29c390(D_00482370, id, 1);
        }
    }
    if (!CharaCountAbilitiesFilteredMaybe_3add30(u, -1, -1, 0)) {
        MenuPartyCmdRowDim_29c390(D_00482370, id, 3 - pos->y);
    }
    return 1;
}
