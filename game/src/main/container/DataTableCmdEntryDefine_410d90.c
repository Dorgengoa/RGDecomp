/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_410d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 pada[0xC - 0xA];
    s32 unkC;
} Elem8C_00410D90;

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7e[0x8C - 0x7E];
    Elem8C_00410D90 *unk8C;
} Obj00410D90;

/*rgp*/
/*rgp*/
/*rgp*/
extern Obj00410D90 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdEntryDefine_410d90(s64 *arg0) {
    Obj00410D90 *o;
    Elem8C_00410D90 *e;
    s16 v;

    o = D_004830F8;
    if (o->unk7C <= 0) {
        return 1;
    }
    if (D_004830FC >= o->unk7C) {
        return 1;
    }
    {
        e = &o->unk8C[D_004830FC];
        e->unk0 = D_004830FC + 1;
        e->unk2 = VariantGetInt_15f780((s32)arg0++);
        e->unk4 = VariantGetInt_15f780((s32)arg0++);
        e->unk6 = VariantGetInt_15f780((s32)arg0++);
        e->unk8 = 0;
        e->unk8 = e->unk8 | (VariantGetInt_15f780((s32)arg0++) > 0);
        if (VariantGetInt_15f780((s32)arg0++) > 0) {
            v = 2;
        } else {
            v = 0;
        }
        e->unk8 = e->unk8 | v;
        if (VariantGetInt_15f780((s32)arg0++) > 0) {
            v = 4;
        } else {
            v = 0;
        }
        e->unk8 = e->unk8 | v;
        e->unkC = DataTableStoreString_368ab0(o, SlotGetInt_15f720((s32)arg0));
        D_004830FC += 1;
        return 1;
    }
    return 1;
}
