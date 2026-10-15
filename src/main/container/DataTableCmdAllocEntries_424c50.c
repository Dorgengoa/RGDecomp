#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8    pad000[0x6C];
    u8    m6C[0x10];
    s16   count;
    u8    pad07E[0xE];
    void *slots;
    u8    pad090[0xC];
    s16   m09C;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern void *ArenaNew_424f40(s32 a, void *b, s32 c, s32 d);
extern void *ConstructNewArray_100710(void *m, void (*f)(void), s32 c, s32 e, s32 n);

s32 DataTableCmdAllocEntries_424c50(R8 *src)
{
    Pool *p = D_004830F8;
    s32 t;
    s32 n;

    t = VariantGetInt_15f780(src);
    if (p->m09C < 0) p->count = t;
    else p->count = 1;
    n = p->count;
    p->slots = ConstructNewArray_100710(ArenaNew_424f40(n * 0x10 + 0x10, p->m6C, 4, -1), 0, 0, 0x10, n);
    D_004830FC = 0;
    return 1;
}
