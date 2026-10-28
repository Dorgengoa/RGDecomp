/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocEntries_405110 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocEntries_405110(void *rgp_a0)
{
    Pool *o = D_004830F8;
    s32 t;
    s32 n;
    s32 r;

    t = VariantGetInt_15f780((void *)rgp_a0);
    n = (s16)t;
    o->m7C = t;
    if (n > 0) {
        r = ((s32)ConstructNewArray_100710(ArenaNew_4049f0((n * 0x3C) + 0x10, o->m6C, o->m80, -1),
                         DataTableRowCtor_4051b0, 0, 0x3C, n));
        o->m8C = r;
        if (r == 0) {
            return 1;
        }
        DataTableAllocBitset_368960(o);
    }
    return 1;
}
