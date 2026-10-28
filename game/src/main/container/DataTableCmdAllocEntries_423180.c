/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocEntries_423180 1
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
    u8    pad090[0x2C];
    s32   m0BC;
    s32   m0C0;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocEntries_423180(R8 *src)
{
    Pool *p = D_004830F8;
    s32 t;
    s32 n;

    t = VariantGetInt_15f780(src);
    p->count = t;
    n = (s16)t;
    if (n > 0) {
        p->slots = ConstructNewArray_100710(ArenaNew_4235b0(n * 0x20 + 0x10, p->m6C, 4, -1), DataTableRowCtor_423210, 0, 0x20, n);
    } else {
        p->slots = 0;
    }
    D_004830FC = 0;
    p->m0BC = 0;
    p->m0C0 = 0;
    return 1;
}
