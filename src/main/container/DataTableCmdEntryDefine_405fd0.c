#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s32 f008;
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
extern s32  ArenaNew_406600(s32 a, void *b, s32 c, s32 d);
extern s32  D_00483C54;

s32 DataTableCmdEntryDefine_405fd0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  t3;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f002 = VariantGetInt_15f780(src++);
    t3 = VariantGetInt_15f780(src);
    e->f006 = t3;
    if ((s16)t3 > 0) e->f008 = ArenaNew_406600((s16)t3 * 0x8, p->m6C, 0x4, -1);
    else e->f008 = 0;
    D_004830FC = D_004830FC + 1;
    D_00483C54 = 0;
    return 1;
}
