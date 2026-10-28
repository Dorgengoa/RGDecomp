/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} BF232670;

typedef struct {
    u8 d[0xB0];
    void *vptr;
    u8 rest[0x7DC];
} Obj232670;

class C232670 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f101(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f139() { return VCM0(s32, 0x234); }
    u8 pad[0x1C4];
    BF232670 bf;
};

extern "C" {
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern u8 *GetGameData_1fede0(void);
extern s32 ObjFindNthAttachPoint_1addc0(s32, s32, s32);
extern s32 *ModelGetFrame_1511f0(s32, s32);
extern void CharaPostUpdateMaybe_20f0b0(u8 *, f32);
extern s32 CharaGetActionMode_213850(u8 *);
extern s32 CharaInvincibleTimeOver_2138b0(u8 *);
extern void CharaRequestTint_213fd0(u8 *, s32, s32, f32, f32, f32, f32, f32);
extern void CharaGaugeFullFxStartMaybe_214250(u8 *);
extern void CharaGaugeDrainFxStartMaybe_214260(u8 *);
extern s32 CharaGetId_214a80(u8 *);
extern s32 CharaGetActionTable_214cd0(u8 *);
extern s32 CharaFlagsA44Test808Related_215010(u8 *);
extern void NodeRefObjCloneAndRegister_219500(Obj232670 *);
extern s32 ActCfgTableGetColPrmValue_223460(s32, s32);
extern void CharaSetVelocity_238770(u8 *, f32, f32, f32);
extern void CharaGetVelocity_238890(u8 *, f32 *);
extern s32 IsInBattleMode_288380(void);
extern s32 IsInBattle_288420(void);
extern void NodeRefObjAddClsnPnt_318ca0(Obj232670 *, s32, s32, f32, f32);
extern s32 NodeRefListAdd_318d50(Obj232670 *, s32, s32, s32, s32, f32 *);
extern void NodeRefObjCtor_318ff0(Obj232670 *, s32, s32, s32, f32);
extern C232670 *ActorFindById_3eb870(u8 *, s32);
extern u8 *DListGetHead_42ea60(u8 *);
extern u8 *DListGetNext_42eb30(u8 *);
extern f32 D_0045B080[];
extern u8 D_00471AA0[];
extern f32 D_0047DB14;
extern f32 D_0047E710;
extern f32 D_0047E714;
extern f32 D_0047E718;
extern f32 D_0047E71C;
}

static inline s32 IsA(u8 *o) {
    return (*(s32 *)(o + 0xA44) & 0x1000) != 0;
}

static inline s32 IsB(u8 *o) {
    return (*(s32 *)(o + 0xA44) & 0x2000) != 0;
}

static inline bool NotA(u8 *o) {
    return !((*(s32 *)(o + 0xA44) & 0x1000) != 0);
}

static inline bool NotB(u8 *o) {
    return !((*(s32 *)(o + 0xA44) & 0x2000) != 0);
}

extern "C" void ActionMgrPostUpdateAll_232670(u8 *arg0) {
    Obj232670 obj __attribute__((aligned(16)));
    f32 col[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    s32 g;
    f32 k21;
    u8 *it;
    f32 k20;
    f32 kb;
    u8 *nx;
    u8 *o;
    u8 *d;
    C232670 *c;
    s32 e;
    s32 tbl;
    s32 fl;
    s32 grp;
    s32 idx;
    s32 *n;
    s32 *s7;
    s32 s6;
    s32 r;
    s32 kk;

    g = GetCurrentScene_1f5be0();
    k21 = GameSceneGetTimeStep_1ceba0(g);
    it = DListGetHead_42ea60(arg0 + 0x20);
    k20 = D_0047DB14 * *(volatile f32 *)&D_0045B080[0];
    while (it != 0) {
        nx = DListGetNext_42eb30(it);
        o = it + 0x10;
        it = nx;
        if (IsInBattleMode_288380() != 0) {
            d = GetGameData_1fede0();
            c = ActorFindById_3eb870(d, ((short)CharaGetId_214a80(o)));
            e = ObjRecGetLiveObject_1c4a90(g, ((short)CharaGetId_214a80(o)));
            tbl = CharaGetActionTable_214cd0(o);
            if (c != 0 && e != 0) {
                c->bf.b1 = (*(s32 *)(o + 0xA44) & 0x10) != 0;
                c->bf.b2 = ((unsigned char)CharaFlagsA44Test808Related_215010(o));
                if (c->f139() != 0 && CharaInvincibleTimeOver_2138b0(o) != 0 && ((short)CharaGetActionMode_213850(o)) != 10) {
                    fl = 2;
                    if (c->f101(fl) != 0) {
                        fl |= 0x4000;
                    }
                    NodeRefObjCtor_318ff0(&obj, 1, ((short)CharaGetId_214a80(o)), fl, 1.0f);
                    for (grp = 0x64; grp <= 0x66; grp++) {
                        idx = 0;
                        while ((n = (s32 *)ObjFindNthAttachPoint_1addc0(e, grp, idx)) != 0) {
                            idx++;
                            if (n[3] == 0) {
                                continue;
                            }
                            s7 = ModelGetFrame_1511f0(e, n[0]);
                            if (s7 == 0) {
                                continue;
                            }
                            col[0] = D_0047E710;
                            col[1] = D_0047E714;
                            col[2] = D_0047E718;
                            col[3] = D_0047E71C;
                            s6 = 0;
                            if (grp == 0x65) {
                                col[0] = *(f32 *)&n[5] * k20;
                                col[1] = *(f32 *)&n[6] * k20;
                                col[2] = *(f32 *)&n[7] * k20;
                            }
                            if (grp == 0x66) {
                                s6 |= 2;
                            }
                            if (tbl != 0) {
                                r = ActCfgTableGetColPrmValue_223460(tbl, s7[0]);
                            } else {
                                r = -1;
                            }
                            kk = NodeRefListAdd_318d50(&obj, ((short)CharaGetId_214a80(o)), -1, s7[0], r, col);
                            NodeRefObjAddClsnPnt_318ca0(&obj, kk, s6, 0.0f, *(f32 *)&n[4] * k20);
                        }
                    }
                    NodeRefObjCloneAndRegister_219500(&obj);
                    obj.vptr = D_00471AA0;
                }
            }
        }
        if (!NotA(o) && NotB(o)) {
            if (((short)CharaGetId_214a80(o)) >= 0 && ((short)CharaGetId_214a80(o)) < 12 && ((unsigned char)IsInBattle_288420()) != 0) {
                CharaRequestTint_213fd0(o, 4, 2, 160.0f, 240.0f, 250.0f, 10.0f, 1.0f);
                CharaGaugeFullFxStartMaybe_214250(o);
                if (GetGameMode_1f59c0() == 7) {
                    GameSceneSoundSlot0PlaySeVol_1d05f0(g, 0x2C, 1.0f);
                }
            }
        }
        if (NotA(o) && !NotB(o)) {
            if (GetGameMode_1f59c0() == 7) {
                GameSceneSoundSlot0PlaySeVol_1d05f0(g, 0x2A, 1.0f);
            }
            CharaGaugeDrainFxStartMaybe_214260(o);
        }
        if (*(s32 *)(o + 0xA44) & 0x40000) {
            ObjRecSetFlags_1c3e00(g, 1, ((short)CharaGetId_214a80(o)), 0x4000000);
        } else {
            ObjRecClearFlags_1c3dc0(g, 1, ((short)CharaGetId_214a80(o)), 0x4000000);
        }
        CharaPostUpdateMaybe_20f0b0(o, k21);
        if (*(s32 *)(arg0 + 0x38) & 0x40000000) {
            *(u64 *)(o + 0x3D0) |= 0x0000400000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000080000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000040000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000020000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000010000000000ULL;
            *(u64 *)(o + 0x3D0) |= 0x0000100000000000ULL;
            CharaGetVelocity_238890(o, v);
            CharaSetVelocity_238770(o, v[0], 0.0f, v[2]);
        }
        if (*(u64 *)(o + 0x3D0) & 0x1000000000000000ULL) {
            ObjRecSetFlags_1c3e00(g, 1, ((short)CharaGetId_214a80(o)), 0x40);
        }
    }
}
