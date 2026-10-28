/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocEntries_416380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8    pad000[0x6C];
    u8    m6C[0x10];
    s16   count;
    u8    pad07E[0xE];
    void *slots;
    u8    pad090[0x4];
    s32   m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocEntries_416380(R8 *src)
{
    Pool *p = D_004830F8;
    s32 t;
    s32 n;

    t = VariantGetInt_15f780(src);
    p->count = t;
    n = (s16)t;
    if (n > 0) {
        p->slots = ConstructNewArray_100710(ArenaNew_4171a0(n * 0x28 + 0x10, p->m6C, 4, -1), DataTableRowCtor_416410, 0, 0x28, n);
    } else {
        p->slots = 0;
    }
    D_004830FC = 0;
    p->m094 = 0;
    return 1;
}
