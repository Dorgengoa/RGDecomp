/* rgp:protos */
#define RGP_SELF_WorldOnPartyLocationChanged_3ec050 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct Msg { u8 b[0x30]; } Msg;

typedef struct Ent {
    u8 pad0[0x10];
    s16 *kind;
} Ent;

typedef struct Obj18 {
    u8 pad0[0x30];
    s16 id;
    u8 pad32[0xE6];
    s64 unk118;
    f32 unk120;
} Obj18;

typedef struct Obj20 {
    u8 pad0[0x24C];
    u8 flags;
} Obj20;

typedef struct Obj34 {
    u8 pad0[0x14];
    s32 tbl;
} Obj34;

typedef struct Obj8 {
    u8 pad0[0x34];
    Obj34 *unk34;
} Obj8;

typedef struct Ctx {
    u8 pad0[8];
    Obj8 *unk8;
    u8 padC[4];
    s32 unk10;
    u8 pad14[4];
    Obj18 *unk18;
    u8 pad1C[4];
    Obj20 *unk20;
    u8 pad24[8];
    u8 flags;
} Ctx;

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

s32 WorldOnPartyLocationChanged_3ec050(Ctx *arg0, s32 arg1, s32 arg2) {
    Msg sp90 __attribute__((aligned(16)));
    Msg sp60 __attribute__((aligned(16)));
    Ent *a;
    Ent *b;
    s32 t;
    s32 k;
    s32 ka;
    s32 kb;
    f32 f;
    Obj18 *o;

    if (arg0->flags & 1) {
        return 0;
    }
    if (arg0->unk8 == NULL) {
        return 0;
    }
    CharaSysClearTables_3a5c00(arg0->unk20);
    a = ((Ent *)GroupTableFindEntry_415e00(arg0->unk8->unk34->tbl, (s16)arg2 / 100, (s16)arg2, 0));
    b = ((Ent *)GroupTableFindEntry_415e00(arg0->unk8->unk34->tbl, (s16)arg1 / 100, (s16)arg1, 0));
    if (a != NULL) {
        t = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&sp90);
        ActionPacketInitAreaChangePosMaybe_3e37d0(&sp90, t, a, 0, 0, 0.0f);
        EventFireTriggers_3e2660(&sp90, 0);
        if (!(arg0->unk20->flags & 1)) {
            t = PartyGetLeaderChara_3c2820(arg0->unk18);
            if (t != 0) {
                SkillTriggerEvalMaybe_3e1200(&sp90, t);
            }
        }
    }
    if (b != NULL) {
        k = *b->kind;
        StateGetChapter_3cd5b0(arg0->unk10);
        switch (k) {
        case 10:
            o = arg0->unk18;
            if (o->id > 20000 && o->id < 21001) {
                PartySelectEncounter_3c9c30(o);
                CharaSysEncounterDistRoll_3a59d0(arg0->unk20, 0);
            }
        }
        t = GetCurrentScene_1f5be0();
        ActionPacketReset_3e3d00(&sp60);
        o = arg0->unk18;
        f = o->unk120;
        k = dptoli(__builtin_bit_cast(double, (long long)(o->unk118)));
        ActionPacketInitAreaChangePosMaybe_3e37d0(&sp60, t, b, 1, k, f);
        EventFireTriggers_3e2660(&sp60, 0);
        if (!(arg0->unk20->flags & 1)) {
            t = PartyGetLeaderChara_3c2820(arg0->unk18);
            if (t != 0) {
                SkillTriggerEvalMaybe_3e1200(&sp60, t);
            }
        }
    }
    if (a != NULL && b != NULL) {
        ka = *a->kind;
        kb = *b->kind;
        if (ka == 10 && kb != 10) {
            StateFlag256Set_3cc4c0(arg0->unk10, 0x80, 0);
        }
    }
    return 1;
}
