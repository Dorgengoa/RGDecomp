#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Sub0 {
    s16 f000;
    s16 f002;
} Sub0;

typedef struct Ent {
    u8  pad000[0xC];
    s16 f00C;
    u8  pad00E[0x2];
    Sub0 *f010;
    u8  pad014[0x8];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x4];
    s16 cnt004;
    u8  pad006[0x2];
    Ent *slots008;
    u8  pad00C[0xC];
} Lvl0;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern void * ArenaNew_409ec0(s32 a, void *b, s32 c, s32 d);
extern s32  D_00480230;

s32 DataTableCmdSubEntryPairList_408f00(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    s32   i1;
    Ent  *e;
    s32  k0;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt004;
    i1 = D_00480230 - 1;
    if (i1 >= n1) return 1;
    e = &e0->slots008[i1];
    t0 = VariantGetInt_15f780(src++);
    e->f00C = t0;
    if ((s16)t0 > 0) e->f010 = ArenaNew_409ec0((s16)t0 * 0x4, p->m6C, 0x4, -1);
    else e->f010 = 0;
    for (k0 = 0; k0 < e->f00C; k0++) {
        e->f010[k0].f002 = VariantGetInt_15f780(src++);
        e->f010[k0].f000 = VariantGetInt_15f780(src++);
    }
    return 1;
}
