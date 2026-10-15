#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x6];
    s16 f008;
    s16 f00A;
    u8  pad00C[0x4];
    s16 f010;
    u8  pad012[0x2];
    s16 f014;
    u8  pad016[0x2];
    s16 f018;
    u8  pad01A[0x2];
    s16 f01C;
    u8  pad01E[0x2];
    void *f020;
    u8  pad024[0x18];
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
extern f32   VariantGetFloat_15f740(R8 *q);
extern void *SlotGetInt_15f720(R8 *q);
extern s32   Base64Decode_36a700(void *b, void *v);
extern void *ArenaAlloc_3702f0(void *h, s32 n, s32 a);
extern void  memcpy(void *, void *, s32);

s32 DataTableCmdEntryBlob_4100e0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  m;
    void *r;
    u8   buf[0x2000];

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    m = Base64Decode_36a700(buf, SlotGetInt_15f720(src++));
    if (m > 2) {
        e->f00A = m - 2;
        r = ArenaAlloc_3702f0(p->m6C, (s16)(m - 2), 0x1);
        e->f020 = r;
        memcpy(r, buf + 2, e->f00A);
    } else {
        e->f000 = 0;
        e->f00A = 0;
        e->f020 = 0;
    }
    e->f010 = VariantGetInt_15f780(src++);
    e->f014 = VariantGetInt_15f780(src++);
    e->f018 = VariantGetInt_15f780(src++);
    e->f01C = VariantGetInt_15f780(src++);
    e->f008 = 100.0f * VariantGetFloat_15f740(src);
    return 1;
}
