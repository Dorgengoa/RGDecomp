#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  f000;
    u8  f001;
} Ent;

typedef struct Lvl2 {
    u8  pad000[0x1];
    u8  cnt001;
    u8  pad002[0x2];
    Ent *slots004;
} Lvl2;
typedef struct Lvl1 {
    u8  pad000[0x2];
    u8  cnt002;
    u8  pad003[0x5];
    Lvl2 *slots008;
} Lvl1;
typedef struct Lvl0 {
    u8  pad000[0x2];
    s16 cnt002;
    Lvl1 *slots004;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern u8   D_00483C78;
extern u8   D_00483C80;
extern u8   D_00483C84;

s32 DataTableCmdSubEntryDefine_406f60(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    Lvl1 *e1;
    s32   n2;
    Lvl2 *e2;
    s32   n3;
    s32   i3;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt002;
    if (D_00483C78 - 1 >= n1) return 1;
    e1 = &e0->slots004[D_00483C78] - 1;
    n2 = e1->cnt002;
    if (D_00483C80 - 1 >= n2) return 1;
    e2 = &e1->slots008[D_00483C80] - 1;
    n3 = e2->cnt001;
    i3 = D_00483C84;
    if (i3 >= n3) return 1;
    e = &e2->slots004[i3];
    e->f000 = VariantGetInt_15f780(src++);
    e->f001 = VariantGetInt_15f780(src);
    D_00483C84 = D_00483C84 + 1;
    return 1;
}
