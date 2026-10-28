#include "types.h"
extern "C" {
#pragma opt_propagation off


typedef struct {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
    s32 unk10;
    u8 pad14[4];
} Elem8C_00429650;

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7e[0x8C - 0x7E];
    Elem8C_00429650 *unk8C;
} Obj00429650;

s32 SlotGetInt_15f720(s32);                              /* extern */
s32 DataTableStoreString_368ab0(Obj00429650 *, s32);               /* extern */
extern Obj00429650 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdEntrySetParams_429650(s64 *arg0) {








    Obj00429650 * o = D_004830F8;
    s32 n = o->unk7C;
    if (n <= 0) {
        return 1;
    }
    s32 i = D_004830FC - 1;
    if (i >= n) {
        return 1;
    }
    Elem8C_00429650 * e = &o->unk8C[i];
    s32 r1 = SlotGetInt_15f720((s32)arg0++);
    s32 r2 = SlotGetInt_15f720((s32)arg0++);
    s32 r3 = SlotGetInt_15f720((s32)arg0++);
    s32 r4 = SlotGetInt_15f720((s32)arg0);
    switch (e->unk4) {
    case 1:
        e->unkC = DataTableStoreString_368ab0(o, r1);
        break;
    case 2:
        e->unkC = DataTableStoreString_368ab0(o, r2);
        e->unk10 = DataTableStoreString_368ab0(o, r3);
        break;
    case 3:
        e->unkC = DataTableStoreString_368ab0(o, r4);
        e->unk10 = DataTableStoreString_368ab0(o, r3);
        break;
    }
    return 1;
}

}
