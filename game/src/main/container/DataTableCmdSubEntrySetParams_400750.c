/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntrySetParams_400750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x4];
    s16 f004;
    s16 f006;
    s16 f008;
    s16 f00A;
    s16 f00C;
    u8  pad00E[0x2];
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x8];
    s16 cnt008;
    u8  pad00A[0x2];
    Ent *slots00C;
    u8  pad010[0x4];
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/

s32 DataTableCmdSubEntrySetParams_400750(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt008;
    if (n1 <= 0) return 1;
    if (p->m094 - 1 >= n1) return 1;
    e = &e0->slots00C[p->m094] - 1;
    e->f004 = VariantGetInt_15f780(src++);
    e->f006 = VariantGetInt_15f780(src++);
    e->f008 = VariantGetInt_15f780(src++);
    e->f00A = VariantGetInt_15f780(src++);
    e->f00C = VariantGetInt_15f780(src);
    return 1;
}
