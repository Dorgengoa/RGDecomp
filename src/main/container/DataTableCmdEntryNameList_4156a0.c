#include "types.h"

typedef struct {
    s16 a;
    s32 b;
} E;

typedef struct {
    u8 pad0[0x1A];
    s16 x1A;
    E *x1C;
    u8 pad20[0xC];
} Item;

extern s32 SlotGetInt_15f720(s64 *arg0);
extern s32 VariantGetInt_15f780(s64 *arg0);
extern s32 DataTableStoreString_368ab0(void *arg0, s32 arg1);
extern E *ArenaNew_4171a0(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern u8 *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdEntryNameList_4156a0(s64 *arg0)
{
    s32 cnt;
    s32 n;
    E *e;
    s32 i;
    Item *it;
    s32 idx;
    u8 *g;

    g = D_004830F8;
    if (*(s16 *)(g + 0x7C) <= 0) {
        return 1;
    }
    idx = D_004830FC - 1;
    if (idx >= *(s16 *)(g + 0x7C)) {
        return 1;
    }

    it = (Item *)(*(u8 **)(g + 0x8C)) + idx;
    n = VariantGetInt_15f780(arg0++);
    it->x1A = n;
    if (n > 0) {
        it->x1C = ArenaNew_4171a0(n * 8, g + 0x6C, 4, -1);
        if (it->x1C != NULL) {
            e = it->x1C;
            for (i = 0; i < n; i++) {
                e->a = VariantGetInt_15f780(arg0++);
                e->b = DataTableStoreString_368ab0(g, SlotGetInt_15f720(arg0++));
                e++;
            }
        }
    } else {
        it->x1C = NULL;
    }
    return 1;
}
