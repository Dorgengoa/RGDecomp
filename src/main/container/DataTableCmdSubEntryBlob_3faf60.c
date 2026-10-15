#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004;
    s16 f008;
    u8  pad00A[0x2];
    void *f00C;
    s16 f010;
    u8  pad012[0x2];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x9];
    s8  b009_0 : 6;
    s8  pb009_6 : 2;
    u8  pad00A[0x2];
    Ent *slots00C;
    u8  pad010[0x4];
} Lvl0;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern void * SlotGetInt_15f720(R8 *q);
extern s32  DataTableStoreString_368ab0(Pool *o, void *v);
extern s32   Base64Decode_36a700(void *b, void *v);
extern void *ArenaAlloc_3702f0(void *h, s32 n, s32 a);
extern void  memcpy(void *, void *, s32);

s32 DataTableCmdSubEntryBlob_3faf60(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    Ent *q1;
    s32   n1;
    s32   i1;
    Ent  *e;
    s32  m0;
    void *r0;
    u8   buf0[0x2000];

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    q1 = e0->slots00C;
    if (q1 == 0) return 1;
    n1 = e0->b009_0;
    if (n1 <= 0) return 1;
    i1 = p->m094;
    if (i1 >= n1) return 1;
    e = &q1[i1];
    e->f000 = VariantGetInt_15f780(src++);
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    m0 = Base64Decode_36a700(buf0, SlotGetInt_15f720(src++));
    e->f008 = m0;
    e->f00C = 0;
    if (m0 > 0) {
        r0 = ArenaAlloc_3702f0(p->m6C, m0, 0x1);
        e->f00C = r0;
        memcpy(r0, buf0, m0);
    }
    e->f010 = VariantGetInt_15f780(src);
    p->m094 = p->m094 + 1;
    return 1;
}
