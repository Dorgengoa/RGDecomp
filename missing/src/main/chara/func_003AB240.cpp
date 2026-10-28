/* rg-missing: func_003AB240 (retail MAIN 0x003AB240, size 0x9A0; no retail name --
 * reads as CharaExecInfoFill, the Chara twin of UnitExecInfoFill_3bd140)
 * why: Chara vtable slot after CharaActionGaugeRegen_3b6490 in the six Chara
 * vtables D_004722A0..D_00473BF0 (battle: weapon attack kind 1, ability kind 3,
 * item kind 4 fill the ExecInfo and its ExecEffInfo list); the snapshot has no C.
 * C++ because retail dispatches Chara/pool/item slots the mwcc C++ way ($t9).
 * `cid = D_004659B0[0]` (a dead variable reused as the clamp), `sc` reused for the
 * battle multiplier and `(bool)` for the guard bit only steer mwcc's register
 * choice (no effect on behaviour).
 * Checked: mwcc 3.0.1b210 -O4 compiles this file to retail's 613 instructions
 * (MATCH, out/missing-staged/README.md). */
#include "types.h"

struct ExecRes {
    u8 pad0[8];
    s32 m8;
    s32 mC;
    s32 m10;
};

#ifdef __MWERKS__
#include "vshim_charaexec.h" /* out/missing-staged/verify: placeholder virtuals at the retail slots */
#define CHARA_GET_STAT38(o, a) (((VCharaExec *)(o))->GetStat38(a))
#define CHARA_SELECT_BTL_EFF_ROW(o, a, b) (((VCharaExec *)(o))->SelectBtlEffRow(a, b))
#define CHARA_GET_STAT248(o, a, b) (((VCharaExec *)(o))->GetStat248(a, b))
#define CHARA_TABLE_3F8(o, a, b) (((VCharaExec *)(o))->Table3F8(a, b))
#define CHARA_TABLE_400(o, a, b) (((VCharaExec *)(o))->Table400(a, b))
#define CHARA_TABLE_408(o, a, b) (((VCharaExec *)(o))->Table408(a, b))
#define CHARA_TABLE_410(o, a, b) (((VCharaExec *)(o))->Table410(a, b))
#define CHARA_TABLE_418(o, a, b, c) (((VCharaExec *)(o))->Table418(a, b, c))
#define CHARA_PENDING_ACT_CANCEL(o) (((VCharaExec *)(o))->PendingActCancel())
#define RES_POOL_GET(o, a) (((VExecResPool *)(o))->Get(a))
#define ITEM_V9C(o, a) (((VExecItem *)(o))->GetV9C(a))
#else
/* Chara vtable slots (D_004722A0): 0x158 CharaGetStat38_29c110, 0x31C
 * CharaSelectBtlEffRowMaybe_3b1850, 0x3F0 CharaGetStat248_29c0e0, 0x3F8..0x410
 * CharaTable2x2Get_*, 0x418 CharaTable2x5x2Get_3abbe0, 0x484 CharaPendingActCancelMaybe_3ac570 */
#define CHARA_GET_STAT38(o, a) VCALL(o, 0, 0x158, u16, (void *, s32), a)
#define CHARA_SELECT_BTL_EFF_ROW(o, a, b) VCALL(o, 0, 0x31C, ExecRes *, (void *, s32, s32), a, b)
#define CHARA_GET_STAT248(o, a, b) VCALL(o, 0, 0x3F0, s32, (void *, s32, s32), a, b)
#define CHARA_TABLE_3F8(o, a, b) VCALL(o, 0, 0x3F8, f32, (void *, s32, s32), a, b)
#define CHARA_TABLE_400(o, a, b) VCALL(o, 0, 0x400, f32, (void *, s32, s32), a, b)
#define CHARA_TABLE_408(o, a, b) VCALL(o, 0, 0x408, f32, (void *, s32, s32), a, b)
#define CHARA_TABLE_410(o, a, b) VCALL(o, 0, 0x410, f32, (void *, s32, s32), a, b)
#define CHARA_TABLE_418(o, a, b, c) VCALL(o, 0, 0x418, s32, (void *, s32, s32, s32), a, b, c)
#define CHARA_PENDING_ACT_CANCEL(o) VCALL0(o, 0, 0x484, void)
#define RES_POOL_GET(o, a) VCALL_SE(o, 0, 0x70, ExecRes *, (void *, s32), a)
#define ITEM_V9C(o, a) VCALL(o, 0, 0x9C, s32, (void *, s32), a)
#endif

typedef struct AbilityRec {
    s16 id;
    u8 pad2;
    u8 m3;
} AbilityRec;

typedef struct EquipSlotX {
    u8 pad0[4];
    AbilityRec *ability;
} EquipSlotX;

typedef struct WeaponUse {
    s16 id;
    u8 pad2[0xA];
    s32 mC;
} WeaponUse;

typedef struct ExecInfo {
    u8 pad0[4];
    s16 kind;
    s16 pad6;
    s16 m8;
    s16 mA;
    union {
        AbilityRec *ability;
        s16 uid;
    } mC;
    s32 m10;
    u8 pad14[4];
    WeaponUse *m18;
    s16 effList;
    s16 pad1E;
    ExecRes *m20;
    ExecRes *m24;
    s16 m28;
    s16 m2A;
    s16 m2C;
    u8 guard : 1;
    u8 m2Erest : 7;
    u8 pad2F;
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
    f32 m40;
    s16 m44;
    s16 m46[5];
    s32 m50;
    s16 m54;
    s16 pad56;
    s32 m58[4];
    s32 m68;
} ExecInfo;

typedef struct CharaExecData {
    u32 vptr;
    u8 pad4[8];
    s32 id;
    u16 m10;
    u8 pad12[0x498 - 0x12];
    EquipSlotX *slot;
    s16 pendingCount;
    s16 pendingKind;
    s32 execCount;
    u8 pad4A4[0x4B0 - 0x4A4];
    s16 itemUseCount;
} CharaExecData;

typedef struct BattleFlags {
    u8 padA[0xA];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 rest : 3;
} BattleFlags;

typedef struct BattleSub {
    u8 pad0[0x2C];
    s16 mode;
    s16 charaId;
    u8 pad30[0x168 - 0x30];
    BattleFlags flags;
} BattleSub;

typedef struct BattleState {
    u8 pad0[0x238];
    BattleSub *sub;
    u8 pad23C[0x24C - 0x23C];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 rest : 3;
} BattleState;

typedef struct GdP54 {
    u8 pad0[8];
    u8 *m8;
} GdP54;

typedef struct GdP8 {
    u8 pad0[0x54];
    GdP54 *m54;
} GdP8;

typedef struct GameDataX {
    u8 pad0[8];
    GdP8 *m8;
    u8 padC[0x18 - 0xC];
    void *inv;
    u8 pad1C[4];
    BattleState *battle;
} GameDataX;

typedef struct ResPoolHolder {
    u8 pad0[8];
    void *pool8;
    void *poolC;
} ResPoolHolder;

typedef struct ExecMgr {
    u8 pad0[0x48];
    ResPoolHolder *m48;
    u8 pad4C[0x54 - 0x4C];
    ResPoolHolder *m54;
} ExecMgr;

#ifndef __MWERKS__
/* port: layout checks (i686 pointers are 4 bytes, so every offset is retail's) */
#define RG_OFS(T, f, o) typedef char rg_ofs_##T##_##f[(__builtin_offsetof(T, f) == (o)) ? 1 : -1]
RG_OFS(ExecInfo, m18, 0x18);
RG_OFS(ExecInfo, m20, 0x20);
RG_OFS(ExecInfo, m30, 0x30);
RG_OFS(ExecInfo, m46, 0x46);
RG_OFS(ExecInfo, m58, 0x58);
RG_OFS(ExecInfo, m68, 0x68);
RG_OFS(CharaExecData, slot, 0x498);
RG_OFS(CharaExecData, itemUseCount, 0x4B0);
RG_OFS(BattleSub, flags, 0x168);
RG_OFS(BattleState, sub, 0x238);
RG_OFS(GameDataX, battle, 0x20);
RG_OFS(ExecMgr, m54, 0x54);
#endif

extern "C" {

extern GameDataX *D_00483818;
extern ExecMgr *D_0048381C;
extern s32 D_004659B0[];

void *InvFindByUniqueId_3c85d0(void *inv, s32 uid, s32 a2, s32 a3);
s32 ItemGetUseEffect_3d4ec0(void *item);
s32 ItemGetWeaponKind_3d4f90(void *item);
s32 ItemGetWeaponUseEffectMaybe_3d4e80(void *item);
void *CharaFindSlotByRecId_3ad390(void *self, s32 id);
s32 EquipSlotGetAbilityEffectRef_3a0480(void *slot);
s32 EquipSlotGetAbilityWeaponSlot_3a06e0(EquipSlotX *slot);
s32 AbilityDataGetCompositeId_3f5e10(AbilityRec *a);
s32 EquipSlotGetAbilityEffectRef2_3a0450(EquipSlotX *slot);
s32 EquipSlotRemapInt_3a0370(EquipSlotX *slot, s32 lv, s32 base);
f32 AbilityDataGetGuardBreakMaybe_3f5850(AbilityRec *a);
s32 AbilityDataRemapInt_3f5a10(AbilityRec *a, s32 lv, s32 base);
f32 AbilityDataGetFloatRelated_3f5950(AbilityRec *a);
f32 AbilityDataGetFloatRelated_3f5920(AbilityRec *a);
f32 AbilityDataGetFloatRelated_3f58f0(AbilityRec *a);
f32 AbilityDataGetFloatRelated_3f58c0(AbilityRec *a);
f32 EquipSlotGetAbilityDamageScaleMaybe_3a03a0(EquipSlotX *slot);
s8 *AbilityDataGetElemAttack_3f5980(AbilityRec *a);
void EquipSlotDrainGaugeOnUse_39ff00(EquipSlotX *slot);
void ExecEffInfoListAdd_3a6cc0(s16 *list, s32 id);

#define CHX(p) ((CharaExecData *)(p))

s32 func_003AB240(CharaExecData *self, ExecInfo *r)
{
    void *item;
    ExecRes *res;
    ExecRes *res2;
    AbilityRec *ab;
    EquipSlotX *slot;
    BattleSub *bs;
    BattleFlags *fl;
    s8 *q;
    s32 kind;
    s32 kindArg;
    s32 eff;
    s32 w;
    s32 cid;
    s32 i;
    s32 v;
    s32 uid;
    f32 sc;
    u8 ok;
    u8 skip;

    if (r == 0) {
        return 0;
    }
    if (D_00483818 == 0) {
        return 0;
    }
    if (D_0048381C == 0) {
        return 0;
    }
    r->effList = 0;
    r->m50 = 0;
    r->m54 = 0;
    for (i = 0; i < 4; i++) {
        r->m58[i] = 0;
    }
    r->m68 = 0;
    self->execCount++;
    switch (r->kind) {
    case 1:
        r->effList = 1;
        ok = 1;
        r->m8 = self->id;
        r->m20 = 0;
        r->m24 = 0;
        r->m28 = 0;
        r->m2A = 0;
        if (r->m18 != 0 && (r->m18->id == 0x258 || r->m18->id == 0x259 || r->m18->id == 0x25F)) {
            ok = 0;
            r->mC.uid = -1;
        }
        item = InvFindByUniqueId_3c85d0(D_00483818->inv, r->mC.uid, -1, 0);
        kind = -1;
        kindArg = 0;
        if (item != 0) {
            kind = ItemGetWeaponKind_3d4f90(item);
            kindArg = kind;
        }
        eff = 0;
        if (item != 0) {
            eff = ItemGetWeaponUseEffectMaybe_3d4e80(item);
        }
        w = 0;
        if (r->m18 != 0) {
            w = r->m18->mC;
        }
        res = CHARA_SELECT_BTL_EFF_ROW(self, eff, w);
        if (res == 0) {
            res = RES_POOL_GET(D_0048381C->m48->poolC, 0x7D0);
        }
        r->m20 = res;
        r->m50 = res->m8;
        if (r->m68 != 0 && item != 0) {
            v = ITEM_V9C(item, 0);
            r->m68 = (s32)RES_POOL_GET(D_0048381C->m54->pool8, (s16)v);
        }
        kindArg = CHARA_GET_STAT248(self, kindArg, 1);
        r->m2C = kindArg;
        r->m30 = 1.0f;
        if (item != 0) {
            r->m34 = CHARA_TABLE_3F8(self, kind, 1);
        } else {
            r->m34 = 1.0f;
        }
        if (item != 0) {
            r->m38 = CHARA_TABLE_400(self, kind, 1);
        } else {
            r->m38 = 0.0f;
        }
        if (item != 0) {
            r->m3C = CHARA_TABLE_408(self, kind, 1);
        } else {
            r->m3C = 1.0f;
        }
        if (item != 0) {
            r->m40 = CHARA_TABLE_410(self, kind, 1);
        } else {
            r->m40 = 0.0f;
        }
        r->m44 = r->m2C;
        if (item != 0) {
            for (i = 0; i < 5; i++) {
                r->m46[i] = CHARA_TABLE_418(self, kind, i, 1);
            }
        }
        if (self->pendingCount > 0) {
            if (self->pendingKind == kind) {
                r->m28 = self->pendingCount;
            }
            CHARA_PENDING_ACT_CANCEL(self);
        }
        if (ok) {
            slot = self->slot;
            if (slot != 0) {
                ab = slot->ability;
                if (kind == EquipSlotGetAbilityWeaponSlot_3a06e0(slot) && ab != 0) {
                    cid = AbilityDataGetCompositeId_3f5e10(ab);
                    eff = EquipSlotGetAbilityEffectRef2_3a0450(self->slot);
                    if (eff != 0) {
                        res2 = CHARA_SELECT_BTL_EFF_ROW(self, eff, w);
                        if (res2 != 0) {
                            skip = 0;
                            if (cid == 0xBB9) {
                                skip = 1;
                            }
                            if (!skip) {
                                r->m24 = res2;
                            }
                            r->m2C = EquipSlotRemapInt_3a0370(self->slot, self->m10, kindArg);
                            r->guard = (bool)AbilityDataGetGuardBreakMaybe_3f5850(ab);
                            if (res2->m8 != 0) {
                                r->m50 = res2->m8;
                            }
                            if (!skip) {
                                ExecEffInfoListAdd_3a6cc0(&r->effList, res2->m10);
                            }
                            r->m34 *= AbilityDataGetFloatRelated_3f5950(ab);
                            r->m38 += AbilityDataGetFloatRelated_3f5920(ab);
                            r->m3C *= AbilityDataGetFloatRelated_3f58f0(ab);
                            r->m40 += AbilityDataGetFloatRelated_3f58c0(ab);
                            if (!(r->m40 <= 100.0f)) {
                                r->m40 = 100.0f;
                            }
                            sc = EquipSlotGetAbilityDamageScaleMaybe_3a03a0(self->slot);
                            if (!(sc <= 0.0f)) {
                                r->m30 *= sc;
                            }
                            if (D_00483818->battle->b4) {
                                sc = *(f32 *)(D_00483818->m8->m54->m8 + 0xBC);
                                r->m30 *= sc;
                                if (r->m30 < 1.0f) {
                                    r->m30 = 1.0f;
                                }
                            }
                            q = AbilityDataGetElemAttack_3f5980(ab);
                            if (q != 0) {
                                cid = D_004659B0[0];
                                for (i = 0; i < 5; i++) {
                                    v = r->m46[i] + q[i];
                                    if (v < 0) {
                                        v = 0;
                                    } else if (cid < v) {
                                        v = cid;
                                    }
                                    r->m46[i] = v;
                                }
                            }
                        }
                    }
                    EquipSlotDrainGaugeOnUse_39ff00(self->slot);
                }
            }
        }
        ExecEffInfoListAdd_3a6cc0(&r->effList, res->m10);
        break;
    case 3:
        r->effList = 3;
        r->m8 = self->id;
        r->m20 = 0;
        ab = r->mC.ability;
        if (ab == 0) {
            return 0;
        }
        slot = (EquipSlotX *)CharaFindSlotByRecId_3ad390((void *)self, ab->id);
        if (slot == 0) {
            return 0;
        }
        eff = EquipSlotGetAbilityEffectRef_3a0480(slot);
        if (eff == 0) {
            return 0;
        }
        res2 = CHARA_SELECT_BTL_EFF_ROW(self, eff, 0);
        if (res2 == 0) {
            res2 = RES_POOL_GET(D_0048381C->m48->poolC, 0x7D0);
        }
        r->m20 = res2;
        r->m50 = res2->m8;
        ExecEffInfoListAdd_3a6cc0(&r->effList, res2->m10);
        r->m2C = AbilityDataRemapInt_3f5a10(ab, self->m10, 0);
        r->guard = (bool)AbilityDataGetGuardBreakMaybe_3f5850(ab);
        r->m30 = 1.0f;
        r->m34 = AbilityDataGetFloatRelated_3f5950(ab);
        r->m38 = AbilityDataGetFloatRelated_3f5920(ab);
        r->m3C = AbilityDataGetFloatRelated_3f58f0(ab);
        r->m40 = AbilityDataGetFloatRelated_3f58c0(ab);
        r->m44 = r->m2C;
        q = AbilityDataGetElemAttack_3f5980(ab);
        if (q != 0) {
            for (i = 0; i < 5; i++) {
                r->m46[i] = q[i];
            }
        }
        if (r->m10 == 0 && res2 != 0) {
            r->m10 = res2->mC;
        }
        bs = D_00483818->battle->sub;
        if (bs != 0) {
            fl = &bs->flags;
            if (bs->mode == 2) {
                fl->b3 = 1;
            }
            if (bs->mode == 1 && (ab->m3 == 1 || ab->m3 == 5) && self->id != bs->charaId) {
                fl->b2 = 1;
            }
        }
        break;
    case 4:
        r->effList = 4;
        r->m8 = self->id;
        r->m20 = 0;
        uid = r->mA;
        item = InvFindByUniqueId_3c85d0(D_00483818->inv, uid, 0, 0);
        if (item == 0) {
            item = InvFindByUniqueId_3c85d0(D_00483818->inv, uid, 9, 0);
        }
        if (item == 0) {
            return 0;
        }
        if (*(s32 *)((u8 *)item + 0x10) == 0) {
            return 0;
        }
        eff = ItemGetUseEffect_3d4ec0(item);
        if (eff == 0) {
            return 0;
        }
        res2 = CHARA_SELECT_BTL_EFF_ROW(self, eff, 0);
        if (res2 == 0) {
            res2 = RES_POOL_GET(D_0048381C->m48->poolC, 0x7D0);
        }
        r->m20 = res2;
        r->m50 = res2->m8;
        ExecEffInfoListAdd_3a6cc0(&r->effList, res2->m10);
        r->m2C = CHARA_GET_STAT38(self, 1);
        r->m30 = 1.0f;
        r->m34 = 0.0f;
        r->m38 = 0.0f;
        r->m3C = 0.0f;
        r->m40 = 0.0f;
        r->m44 = r->m2C;
        for (i = 0; i < 5; i++) {
            r->m46[i] = 0;
        }
        if (r->m10 == 0 && res2 != 0) {
            r->m10 = res2->mC;
        }
        self->itemUseCount++;
        bs = D_00483818->battle->sub;
        if (bs != 0) {
            fl = &bs->flags;
            if (bs->mode == 2) {
                fl->b4 = 1;
            }
        }
        break;
    }
    return 1;
}

}
