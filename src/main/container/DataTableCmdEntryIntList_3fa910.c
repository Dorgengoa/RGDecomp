#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Sub0 {
    s16 f000;
    u8  pad002[0x2];
} Sub0;

typedef struct Ent {
    u8  pad000[0x24];
    s16 f024;
    u8  pad026[0x2];
    Sub0 *f028;
    u8  pad02C[0x4];
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
extern s32  VariantGetInt_15f780(R8 *q);
extern void * ArenaNew_3fb640(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdEntryIntList_3fa910(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    Sub0 *w0;
    s32  k0;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src++);
    e->f024 = t0;
    if ((s16)t0 > 0) e->f028 = ArenaNew_3fb640((s16)t0 * 0x4, p->m6C, 0x4, -1);
    else e->f028 = 0;
    w0 = e->f028;
    for (k0 = 0; k0 < e->f024; k0++) {
        w0->f000 = VariantGetInt_15f780(src++);
        w0++;
    }
    return 1;
}
