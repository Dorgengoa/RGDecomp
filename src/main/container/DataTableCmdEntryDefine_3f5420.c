#include "types.h"

typedef struct Entry003f5420 {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    u8 pad10[0xC];
} Entry003f5420;

typedef struct Ctx003f5420 {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E];
    Entry003f5420 *unk8C;
} Ctx003f5420;

extern s32 SlotGetInt_15f720(s32 arg0);
extern s32 VariantGetInt_15f780(s32 arg0);
extern s32 DataTableStoreString_368ab0(Ctx003f5420 *arg0, s32 arg1);
extern s32 ArenaNew_3f5e90(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern Ctx003f5420 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdEntryDefine_3f5420(s64 *arg0)
{
    Ctx003f5420 *c;
    Entry003f5420 *e;
    s16 n;

    c = D_004830F8;
    n = c->unk7C;
    if (n <= 0) {
        return 1;
    }
    if (D_004830FC >= n) {
        return 1;
    }
    {
        e = &c->unk8C[D_004830FC];
        e->unk0 = VariantGetInt_15f780((s32)arg0++);
        SlotGetInt_15f720((s32)arg0++);
        e->unk8 = DataTableStoreString_368ab0(c, SlotGetInt_15f720((s32)arg0++));
        e->unk2 = VariantGetInt_15f780((s32)arg0++);
        e->unk3 = VariantGetInt_15f780((s32)arg0++);
        e->unk4 = VariantGetInt_15f780((s32)arg0++);
        e->unk5 = VariantGetInt_15f780((s32)arg0);
        e->unkC = 0;
        if (e->unk2 == 0) {
            e->unkC = ArenaNew_3f5e90(0x50, (u8 *)c + 0x6C, 4, -1);
        } else if (e->unk2 == 1) {
            e->unkC = ArenaNew_3f5e90(0x1A, (u8 *)c + 0x6C, 4, -1);
        }
        D_004830FC += 1;
        return 1;
    }
    return 1;
}
