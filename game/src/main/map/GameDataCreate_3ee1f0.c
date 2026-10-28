/* rgp:protos */
#define RGP_SELF_GameDataCreate_3ee1f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct Elem { u8 b[0x60]; } Elem;
typedef struct Obj { void *vt; void *vt2; } Obj;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00471FE0[0x400];
extern u8 D_004721F0[0x400];
extern u8 D_00472250[0x400];
extern u8 D_00472260[0x400];
extern u8 D_0047227C[0x400];
extern u8 D_00474680[0x400];
extern u8 D_004746A0[0x400];
extern u8 D_00475840[0x400];
extern u8 D_00475870[0x400];
extern u8 D_00476160[0x400];
extern u8 D_004761A0[0x400];
extern u8 D_0047CD10[0x400];

typedef struct {
    u8 pad0[0x4];
    u8 *heap;
    u8 pad8[0x4];
    Obj *unkC;
    Obj *unk10;
    Obj *unk14;
    Obj *unk18;
    Obj *unk1C;
    Obj *unk20;
    Obj *unk24;
    Obj *unk28;
    u8 pad2C[0x4];
    s16 unk30;
} T3ee1f0_arg0;

#define HEAPFREE(h) (*(s32 *)((h) + 0x34) - *(s32 *)((h) + 0x2C))

s32 GameDataCreate_3ee1f0(T3ee1f0_arg0 *self, u8 *heap) {
    Obj *p;
    Obj *q;
    u8 *it;
    s32 i;
    s32 before;

    if (heap == 0) {
        return 0;
    }
    GameDataInit_3ee5b0(self);
    self->heap = heap;
    before = HEAPFREE(heap);

    p = ((Obj *)MemStackNew_14e130(0x30, heap));
    if (p != 0) {
        p->vt = D_00471FE0;
        p->vt = D_00476160;
        OptionsInit_3d6340(p);
    }
    self->unkC = p;
    if (p == 0) return 0;

    p = ((Obj *)MemStackNew_14e130(0x2328, self->heap));
    if (p != 0) {
        p->vt = D_00471FE0;
        p->vt = D_00475870;
        Bitset2048Ctor_3eee50((u8 *)p + 0x28);
        Bitset2048Ctor_3eee50((u8 *)p + 0x228);
        Bitset256Ctor_3eee80((u8 *)p + 0x328);
        Bitset1280Ctor_3eeeb0((u8 *)p + 0x360);
        StateBlockInit_3cd890(p, 0, 0, 0);
    }
    self->unk10 = p;
    if (p == 0) return 0;

    p = ((Obj *)MemStackNew_14e130(0xC, self->heap));
    if (p != 0) {
        p->vt = D_00471FE0;
        p->vt2 = D_00472250;
        p->vt2 = D_004761A0;
        p->vt = D_00472260;
        p->vt2 = D_0047227C;
        CharaMgrPoolReset_3a9370(p);
    }
    self->unk14 = p;
    if (p == 0) return 0;

    p = ((Obj *)MemStackNew_14e130(0x4CB0, self->heap));
    if (p != 0) {
        p->vt = D_00471FE0;
        p->vt = D_00475840;
        Bitset131072Ctor_3eeee0((u8 *)p + 0x2D0);
        PartyClearAndReset_3cb840(p);
    }
    self->unk18 = p;
    if (p == 0) return 0;

    p = ((Obj *)MemStackNew_14e130(0x54, self->heap));
    if (p != 0) {
        p->vt = D_00472250;
        p->vt = D_004746A0;
        p->vt = D_00474680;
        ObjMgrResetFields_3bc390(p);
    }
    self->unk1C = p;
    if (p == 0) return 0;

    if ((q = ((Obj *)MemStackNew_14e130(0xB98, self->heap))) != 0) {
        q->vt = D_00471FE0;
        q->vt = D_004721F0;
        it = (u8 *)q + 0x58;
        do {
            BattleRecordReset_3a7fd0(it);
            it += 0x60;
        } while (it < (u8 *)q + 0x238);
        BattleHistoryReset_3a7f30((u8 *)q + 0x28);
        CharaSysReset_3a5ec0(q);
    }
    self->unk20 = q;
    if (q == 0) return 0;

    p = ((Obj *)MemStackNew_14e130(0x118C, self->heap));
    if (p != 0) {
        p->vt = D_00471FE0;
        p->vt = D_0047CD10;
        InsectTeamTableClear_431e00(p);
    }
    self->unk24 = p;
    if (p == 0) return 0;

    p = ((Obj *)MemStackNew_14e130(0x10, self->heap));
    if (p != 0) {
        p = ((Obj *)DataTableOwnerCtor_3b8cf0(p));
    }
    self->unk28 = p;
    if (p == 0) return 0;

    if (self->unkC != 0) OptionsHeapInit_3d6310(self->unkC, self->heap);
    if (self->unk10 != 0) StateBlockCreate_3cd800(self->unk10, self->heap, 0, 0);
    if (self->unk14 != 0) CharaMgrPoolInit_3a92c0(self->unk14, self->heap);
    if (self->unk18 != 0) PartyInit_3cb6b0(self->unk18, self->heap, 0, 0);
    if (self->unk1C != 0) ObjMgrInit_3bc2d0(self->unk1C, self->heap);
    if (self->unk20 != 0) CharaSysInit_3a5d40(self->unk20, self->heap);
    if (self->unk24 != 0) InsectTeamTableInit_431da0(self->unk24, self->heap);
    if (self->unk28 != 0) DataTableOwnerInit_3b8c40(self->unk28, self->heap);
    self->unk30 = before - HEAPFREE(self->heap);
    return 1;
}
