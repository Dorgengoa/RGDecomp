/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocSubEntries_3fb0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x9];
    s8  b009_0 : 6;
    s8  pb009_6 : 2;
    u8  pad00A[0x2];
    s32 f00C;
    u8  pad010[0x4];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocSubEntries_3fb0c0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b009_0 = (s8)VariantGetInt_15f780(src);
    if (e->b009_0 > 0) e->f00C = ((s32)ConstructNewArray_100710(ArenaNew_3fb640(e->b009_0 * 0x14 + 0x10, p->m6C, 0x4, -1), 0, 0, 0x14, e->b009_0));
    else e->f00C = 0;
    p->m094 = 0;
    return 1;
}
