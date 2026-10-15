#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8    pad000[0x6C];
    u8    m6C[0x10];
    s16   count;
    u8    pad07E[0x2];
    s16   m080;
    u8    pad082[0xA];
    void *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32  VariantGetInt_15f780(R8 *q);
extern u8   D_00483C78;
extern u8   D_00483C7C;
extern u8   D_00483C80;
extern u8   D_00483C84;
extern void *ArenaNew_407f50(s32 a, void *b, s32 c, s32 d);
extern void *ConstructNewArray_100710(void *m, void (*f)(void), s32 c, s32 e, s32 n);
extern void  DataTableRowCtor_407880(void);

s32 DataTableCmdAllocEntries_4077e0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 t;
    s32 n;

    t = VariantGetInt_15f780(src);
    p->count = t;
    n = (s16)t;
    if (n > 0) {
        p->slots = ConstructNewArray_100710(ArenaNew_407f50(n * 0x8 + 0x10, p->m6C, p->m080, -1), DataTableRowCtor_407880, 0, 8, n);
        if (p->slots == 0) return 1;
    }
    D_004830FC = 0;
    D_00483C78 = 0;
    D_00483C7C = 0;
    D_00483C80 = 0;
    D_00483C84 = 0;
    return 1;
}
