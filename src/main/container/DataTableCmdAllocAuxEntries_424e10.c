#include "types.h"

typedef struct Pool {
    u8  pad000[0x6C];
    u8  m6C[0x10];
    s16 m7C;
    u8  pad07E[0x16];
    s16 m94;
    u8  pad096[0x2];
    s32 m98;
} Pool;

extern Pool *D_004830F8;
extern s32  D_00483F0C;
extern s32  VariantGetInt_15f780(void);
extern s32  ArenaNew_424f40(s32 a, void *b, s32 c, s32 d);

s32 DataTableCmdAllocAuxEntries_424e10(void)
{
    Pool *p = D_004830F8;
    s32 t;

    t = VariantGetInt_15f780();
    p->m94 = t;
    p->m98 = ArenaNew_424f40((s16)t * 0xC, p->m6C, 4, -1);
    D_00483F0C = 0;
    return 1;
}
