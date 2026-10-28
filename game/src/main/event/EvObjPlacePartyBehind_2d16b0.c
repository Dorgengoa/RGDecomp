/* rgp:protos */
#define RGP_SELF_EvObjPlacePartyBehind_2d16b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Mtx {
    Vec4 v[3];
    f32 f30;
    f32 f34;
} Mtx;

typedef struct PInfo {
    u8 pad0[0x30];
    s16 f30;
    u8 pad32[0x15C];
    s16 f18E;
} PInfo;

typedef struct Party {
    u8 pad0[0x18];
    PInfo *f18;
} Party;

typedef struct Self {
    u8 pad0[0xD0];
    s32 fD0;
} Self;

typedef struct Chr {
    u8 pad0[0x3D8];
    s32 f3D8;
} Chr;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];
extern f32 D_0047EE20;
extern f32 D_0047EE24;
extern f32 D_0047EE28;
extern f32 D_0047EE2C;

void EvObjPlacePartyBehind_2d16b0(Self *self)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[(0x0 - __builtin_offsetof(Mtx, v)) + sizeof(Mtx)]; char m1[0x40]; })];
    Vec4 spB0 __attribute__((aligned(16)));
    Vec4 col __attribute__((aligned(16)));
    Vec4 out __attribute__((aligned(16)));
    f32 a;
    f32 c;
    f32 base;
    f32 b;
    Party *party;
    s32 g;
    s32 h;
    s32 game;
    Chr *chr;
    s32 obj;
    s32 *pp;
    s32 n;
    s32 n2;
    s32 i;
    s32 id;

    if (self == 0) {
        return;
    }
    if (!(self->fD0 & 0x08000000)) {
        return;
    }
    party = ((Party *)GetGameData_1fede0());
    g = ((s32)GetMapMgr_201a90());
    GetCurrentScene_1f5be0();
    h = MapSlotsFindActiveBlockById_1e4730(g, party->f18->f30, 0);
    if (h == 0 || ((unsigned char)MapDataIsJasterOnly_1e7a90(h)) != 0) {
        return;
    }
    GetEventObjMgr_2d1960();
    game = ((s32)GetActionMgr_1fdb50());
    chr = ((Chr *)ActionMgrFindById_233b50(game, party->f18->f18E));
    if (chr == 0) {
        return;
    }
    obj = ((s32)EvObjGetXform_2f9c90(self));
    XformGetUnscaledMatrix_2e7760(obj, (*(Mtx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Mtx, v)))).v);
    EventObjGetRot_2e7670(obj, &spB0);
    if (chr->f3D8 & 4) {
        (*(Mtx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Mtx, v)))).f34 = CharaGetGroundY_238350(chr);
    }
    n = PartyCountExcludingLeader_3c2610(party->f18, 1, 1);
    n2 = n;
    for (i = 0; i < n2; i++) {
        id = ((short)PartyGetNonLeaderId_3c2750(party->f18, i));
        chr = ((Chr *)ActionMgrFindById_233b50(game, id));
        if (chr == 0) {
            continue;
        }
        pp = ((s32 *)CharaGetEvObjContact_214990(chr));
        if (CharaEvObjContactFlag4Related_214860(chr) != 0 && ((unsigned char)StrEqualNonNull_1ca6c0(*pp, EventRecGetKey_2e5730(self))) != 0) {
            continue;
        }
        { f32 *pf = (f32 *)&col;
        pf[0] = D_0047EE20;
        pf[1] = *(volatile f32 *)&D_0047EE24;
        pf[2] = *(volatile f32 *)&D_0047EE28;
        pf[3] = D_0047EE2C; }
        col.z = -1.25f * D_0045B080[0];
        if (n == 2) {
            if (i == 0) {
                col.x = D_0045B080[0];
                col.y = 0.0f;
                col.z = -1.5f * D_0045B080[0];
                col.w = 1.0f;
            } else {
                col.x = -1.0f * D_0045B080[0];
                col.y = 0.0f;
                col.z = -1.5f * D_0045B080[0];
                col.w = 1.0f;
            }
        }
        MatMulPoint_1cb8e0(&out, (*(Mtx *)(rgp_blk1 + (0x0 - __builtin_offsetof(Mtx, v)))).v, &col);
        CharaPlaceAt_2f3a40(id, &out, 0xF, spB0.y);
    }
}
