#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x8];
    s16 f008;
    u8  pad00A[0x6];
    void *f010;
    u8  pad014[0x4];
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
extern void * SlotGetInt_15f720(R8 *q);
extern s32   Base64Decode_36a700(void *b, void *v);
extern void *ArenaAlloc_3702f0(void *h, s32 n, s32 a);
extern void  memcpy(void *, void *, s32);

s32 DataTableCmdEntryBlob_3ff840(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  m0;
    void *r0;
    u8   buf0[0x2000];

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    m0 = Base64Decode_36a700(buf0, SlotGetInt_15f720(src));
    e->f008 = m0;
    e->f010 = 0;
    if (m0 > 0) {
        r0 = ArenaAlloc_3702f0(p->m6C, m0, 0x1);
        e->f010 = r0;
        memcpy(r0, buf0, m0);
    }
    return 1;
}
