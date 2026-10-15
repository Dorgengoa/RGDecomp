#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    u8  pad006[0x2];
    void *f008;
    s16 f00C;
    u8  pad00E[0x2];
    void *f010;
    s16 f014;
    u8  b016_0 : 1;
    u8  pb016_1 : 7;
    u8  pad017[0x5];
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
extern s32   Base64Decode_36a700(void *b, void *v);
extern void *ArenaAlloc_3702f0(void *h, s32 n, s32 a);
extern void  memcpy(void *, void *, s32);

s32 DataTableCmdEntryDefine_412bf0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  m0;
    void *r0;
    u8   buf0[0x2000];
    s32  m1;
    void *r1;
    u8   buf1[0x2000];

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = i;
    e->f002 = VariantGetInt_15f780(src++);
    m0 = Base64Decode_36a700(buf0, SlotGetInt_15f720(src++));
    e->f004 = m0;
    e->f008 = 0;
    if (m0 > 0) {
        r0 = ArenaAlloc_3702f0(p->m6C, m0, 0x1);
        e->f008 = r0;
        memcpy(r0, buf0, m0);
    }
    m1 = Base64Decode_36a700(buf1, SlotGetInt_15f720(src++));
    e->f00C = m1;
    e->f010 = 0;
    if (m1 > 0) {
        r1 = ArenaAlloc_3702f0(p->m6C, m1, 0x1);
        e->f010 = r1;
        memcpy(r1, buf1, m1);
    }
    e->f014 = VariantGetInt_15f780(src++);
    e->b016_0 = VariantGetInt_15f780(src) != 0;
    D_004830FC = D_004830FC + 1;
    return 1;
}
