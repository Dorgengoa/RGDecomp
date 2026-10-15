#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    u8  b004_0 : 2;
    u8  b004_2 : 6;
    u8  pad005[0x3];
    s32 *f008;
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32   VariantGetInt_15f780(R8 *q);
extern void *SlotGetInt_15f720(R8 *q);
extern s32   DataTableStoreString_368ab0(Pool *o, void *v);
extern s32  *ArenaNew_3f7400(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdEntryDefine_3f6ae0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = i;
    e->f002 = VariantGetInt_15f780(src++);
    e->b004_0 = VariantGetInt_15f780(src++);
    e->b004_2 = VariantGetInt_15f780(src++);
    if ((u8)(s32)e->b004_2 > 0) {
        e->f008 = ArenaNew_3f7400((u8)(s32)e->b004_2 * 0x4, p->m6C, 0x4, -1);
        for (k = 0; k < e->b004_2; k++)
            e->f008[k] = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    } else {
        e->b004_2 = 0;
    }
    D_004830FC = D_004830FC + 1;
    return 1;
}
