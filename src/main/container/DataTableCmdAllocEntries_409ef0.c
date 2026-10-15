#include "types.h"

typedef struct Pool {
    u8  pad000[0x6C];
    u8  m6C[0x10];
    s16 m7C;
    s16 pad07E;
    s16 m80;
    u8  pad082[0xA];
    s32 m8C;
} Pool;

extern Pool *D_004830F8;
extern s16  VariantGetInt_15f780(void);
extern s32  ArenaNew_409ec0(s32 a, void *b, s32 c, s32 d);
extern s32  ConstructNewArray_100710(s32 a, void *b, s32 c, s32 d, s32 e);
extern void DataTableAllocBitset_368960(Pool *o);

s32 DataTableCmdAllocEntries_409ef0(void)
{
    Pool *o = D_004830F8;
    s32 t;
    s32 n;
    s32 r;

    t = VariantGetInt_15f780();
    n = (s16)t;
    o->m7C = t;
    if (n > 0) {
        r = ConstructNewArray_100710(ArenaNew_409ec0((n * 0x754) + 0x10, o->m6C, o->m80, -1),
                         0, 0, 0x754, n);
        o->m8C = r;
        if (r == 0) {
            return 1;
        }
        DataTableAllocBitset_368960(o);
    }
    return 1;
}
