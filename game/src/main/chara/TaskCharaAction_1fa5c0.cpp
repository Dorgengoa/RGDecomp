/* rgp:protos */
#line 1
#pragma opt_loop_invariants off
#include "types.h"

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 motion(s32 k) { return VCM(s32, (void *, s32), 0x3E4, k); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * cur() { return VCM0(void *, 0x470); }
};

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 isValid() { return VCM0(s32, 0x48); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 isActive() { return VCM0(s32, 0xC0); }
};

typedef struct Sub { u8 pad[0x18E]; s16 m18E; } Sub;
typedef struct Ctx { u8 pad[0x18]; Sub *m18; } Ctx;

extern "C" {
extern u8 D_004B8680[];
extern char D_0045BD20[];
extern char D_0045BD38[];
extern char D_0045BD40[];
extern char D_0045BD50[];
Ctx *GetGameData_1fede0(void);
s32 GetCurrentScene_1f5be0(void);
s32 ActionMgrFindById_233b50(void *tbl, s32 i);
void ObjRecClearFlags_1c3dc0(s32 w, s32 a, s32 i, s32 m);
void ObjRecSetFlags_1c3e00(s32 w, s32 a, s32 i, s32 m);
s32 ObjRecGetFlags_1c3d90(s32 w, s32 a, s32 i);
void GameSceneObjSetCBlurMaybe_1cf900(s32, s32, f32, s32);
void CharaSetAbltName_2137e0(s32 e, s32 v);
s32 IsInBattleMode_288380(void);
s32 IsInBattle_288420(void);
s32 CharaGetId_214a80(s32 e);
Chr *PartyFindActiveChara_3c2350(Sub *s, s32 v);
s32 EquipSlotGetAbilityCompositeId_3a0730(void *v);
Unit *ActorFindById_3eb870(Ctx *c, s32 i);
void CharaAddFlags_212460(s32 e, u64 f);
s32 CharaGetActionMode_213850(s32 e);
void CharaRequestBattleEnter_213ec0(s32 e, s32 v);
void ActionMgrRunActions_231f90(void *tbl);
s32 CharaGetActionCategory_213690(s32 e);
void PartyTendencyUpdateMaybe_3c8f60(Sub *s, s32 v);
}

extern "C" void TaskCharaAction_1fa5c0(void)
{
    Ctx *ctx;
    u8 *tbl;
    s32 w;
    s32 i;
    s32 e;
    s32 k;
    s32 end;

    ctx = GetGameData_1fede0();
    tbl = D_004B8680;
    w = GetCurrentScene_1f5be0();
    for (i = 0; i < 0xE0; i++) {
        e = ActionMgrFindById_233b50(tbl, i);
        if (e == 0) {
            continue;
        }
        ObjRecClearFlags_1c3dc0(w, 1, i, 0x2000000);
        if (i >= 0 && i < 12) {
            for (end = (i + 1) * 4 + 11, k = i * 4 + 12; k <= end; k++) {
                ObjRecClearFlags_1c3dc0(w, 1, k, 0x2000000);
            }
        }
        CharaSetAbltName_2137e0(e, 0);
        if (IsInBattleMode_288380() != 0) {
            Chr *o = PartyFindActiveChara_3c2350(ctx->m18, ((short)CharaGetId_214a80(e)));
            if (o != 0) {
                s32 f = 0;
                void *v;
                switch (((short)CharaGetId_214a80(e))) {
                case 5:
                    f = 1;
                }
                CharaSetAbltName_2137e0(e, o->motion(f));
                v = o->cur();
                if (v != 0) {
                    k = i;
                    switch (EquipSlotGetAbilityCompositeId_3a0730(v)) {
                    case 0x3EF:
                        CharaSetAbltName_2137e0(e, (s32)D_0045BD20);
                        break;
                    case 0x3EC:
                        CharaSetAbltName_2137e0(e, (s32)D_0045BD38);
                        break;
                    case 0x3EB:
                    case 0x7D3:
                        CharaSetAbltName_2137e0(e, (s32)D_0045BD40);
                        break;
                    case 0x1773:
                        CharaSetAbltName_2137e0(e, (s32)D_0045BD50);
                        k = (i >= 0 && i < 12) ? i * 4 + 14 : -1;
                        break;
                    }
                    ObjRecSetFlags_1c3e00(w, 1, k, 0x2000000);
                }
            }
        }
        GameSceneObjSetCBlurMaybe_1cf900(w, i, 1.0f, ObjRecGetFlags_1c3d90(w, 1, i) & 0x2000000);
        if (i >= 0 && i < 12) {
            for (end = (i + 1) * 4 + 11, k = i * 4 + 12; k <= end; k++) {
                GameSceneObjSetCBlurMaybe_1cf900(w, k, 1.0f, ObjRecGetFlags_1c3d90(w, 1, k) & 0x2000000);
            }
        }
        {
            Unit *u = ActorFindById_3eb870(ctx, i);
            if (u != 0 && u->isActive() != 0 && (((unsigned char)IsInBattle_288420()) != 0 || u->isValid() != 0)) {
                CharaAddFlags_212460(e, (u64)0x800 << 32);
            } else if (i >= 0 && i < 12 && ((short)CharaGetActionMode_213850(e)) == 0x11) {
                CharaAddFlags_212460(e, (u64)0x1000 << 32);
                if (((unsigned char)IsInBattle_288420()) != 0) {
                    CharaRequestBattleEnter_213ec0(e, 0);
                }
            }
        }
    }
    ActionMgrRunActions_231f90(tbl);
    e = ActionMgrFindById_233b50(tbl, ctx->m18->m18E);
    if (e != 0) {
        PartyTendencyUpdateMaybe_3c8f60(ctx->m18, CharaGetActionCategory_213690(e));
    }
}
