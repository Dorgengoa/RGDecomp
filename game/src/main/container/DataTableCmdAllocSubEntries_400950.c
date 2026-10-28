/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocSubEntries_400950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x8];
    s16 f008;
    u8  pad00A[0x2];
    void *f00C;
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

s32 DataTableCmdAllocSubEntries_400950(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src);
    e->f008 = t0;
    if ((s16)t0 > 0) e->f00C = ConstructNewArray_100710(ArenaNew_4018b0((s16)t0 * 0x10 + 0x10, p->m6C, 0x4, -1), 0, 0, 0x10, (s16)t0);
    else e->f00C = 0;
    p->m094 = 0;
    return 1;
}
