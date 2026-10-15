#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8   pad000[0x10];
    s16  f010;
    u8   pad012[0x2];
    s16 *f014;
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0xC];
    s16  m09C;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern s16 *ArenaNew_4171a0(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdEntryIdList_414180(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s16 *r;
    s32 k;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f010 = VariantGetInt_15f780(src++);
    p->m09C = p->m09C + e->f010;
    if (e->f010 > 0) {
        r = e->f014 = ArenaNew_4171a0(e->f010 * 0x2, p->m6C, 0x4, -1);
        for (k = 0; k < e->f010; k++) {
            *r = VariantGetInt_15f780(src++);
            r++;
        }
    } else {
        e->f010 = 0;
        e->f014 = 0;
    }
    return 1;
}
