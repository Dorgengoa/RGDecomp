#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct E {
    s16  m0;
    s16  m2;
    s16  m4;
    s16  m6;
    s16 *m8;
} E;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x28];
    s16  m94;
    s16  pad096;
    E   *m98;
} Pool;

extern Pool *D_004830F8;
extern s32   D_00483F0C;
extern s32   VariantGetInt_15f780(R8 *q);
extern s16  *ArenaNew_424f40(s32 sz, void *m, s32 c, s32 d);

s32 DataTableCmdAuxEntryDefine_424ce0(R8 *a)
{
    Pool *p = D_004830F8;
    E   *e;
    s32  t;
    s16 *q;
    s32  i;

    if (p->m98 == 0) return 1;
    if (p->m94 <= 0) return 1;
    if (D_00483F0C >= p->m94) return 1;
    e = &p->m98[D_00483F0C];
    e->m0 = VariantGetInt_15f780(a++);
    e->m2 = VariantGetInt_15f780(a++);
    e->m4 = VariantGetInt_15f780(a++);
    t = VariantGetInt_15f780(a++);
    e->m6 = t;
    if ((s16)t > 0) {
        e->m8 = ArenaNew_424f40((s16)t * 2, p->m6C, 4, -1);
    } else {
        e->m8 = 0;
    }
    q = e->m8;
    if (q != 0) {
        for (i = 0; i < e->m6; i++) {
            *q = VariantGetInt_15f780(a++);
            q++;
        }
    }
    D_00483F0C++;
    return 1;
}
