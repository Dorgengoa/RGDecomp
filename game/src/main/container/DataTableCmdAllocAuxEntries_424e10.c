/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocAuxEntries_424e10 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocAuxEntries_424e10(void *rgp_a0)
{
    Pool *p = D_004830F8;
    s32 t;

    t = VariantGetInt_15f780((void *)rgp_a0);
    p->m94 = t;
    p->m98 = ArenaNew_424f40((s16)t * 0xC, p->m6C, 4, -1);
    D_00483F0C = 0;
    return 1;
}
