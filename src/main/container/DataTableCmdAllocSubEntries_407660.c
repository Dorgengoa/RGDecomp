#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x2];
    s16 f002;
    void *f004;
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0x2];
    s16  m080;
    u8   pad082[0xA];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern u8   D_00483C78;
extern u8   D_00483C7C;
extern u8   D_00483C80;
extern u8   D_00483C84;
extern void DataTableRowCtor_407740(void);
extern void *ArenaNew_407f50(s32, void *, s32, s32);
extern void *ConstructNewArray_100710(void *, void *, s32, s32, s32);

s32 DataTableCmdAllocSubEntries_407660(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src);
    e->f002 = t0;
    if ((s16)t0 > 0) {
        e->f004 = ConstructNewArray_100710(ArenaNew_407f50((s16)t0 * 0xC + 0x10, p->m6C, p->m080, -1), DataTableRowCtor_407740, 0, 0xC, (s16)t0);
        if (e->f004 == 0) return 1;
    }
    D_00483C78 = 0;
    D_00483C7C = 0;
    D_00483C80 = 0;
    D_00483C84 = 0;
    return 1;
}
