#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec0 {
    s16 f000;
    u8  pad002[0x2];
} Rec0;

typedef struct Ent {
    u8  pad000[0xC];
    s16 f00C;
    u8  pad00E[0x2];
    Rec0 *f010;
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
extern void * ArenaNew_40ac80(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdEntryIntList_40a7d0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  c0;
    Rec0 *q0;
    s32  k0;
    s32  v0;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src++);
    e->f00C = t0;
    if ((s16)t0 > 0) {
        c0 = 0;
        e->f010 = ArenaNew_40ac80((s16)t0 * 0x4, p->m6C, 0x4, -1);
        q0 = e->f010;
        for (k0 = 0; k0 < e->f00C; k0++) {
            v0 = VariantGetInt_15f780(src++);
            if (v0 >= 0) {
                q0->f000 = v0;
                c0++;
                q0++;
            }
        }
        e->f00C = c0;
    }
    else e->f010 = 0;
    return 1;
}
