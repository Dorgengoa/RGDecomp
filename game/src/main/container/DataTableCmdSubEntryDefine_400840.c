/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_400840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    __extension__ signed int b000_0 : 10;
    signed int b000_10 : 20;
    signed int pb000_30 : 2;
    u8  pad004[0xC];
} __attribute__((aligned(4))) Ent;

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

s32 DataTableCmdSubEntryDefine_400840(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    s32   i1;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt008;
    if (n1 <= 0) return 1;
    i1 = p->m094;
    if (i1 >= n1) return 1;
    e = &e0->slots00C[i1];
    e->b000_0 = (s16)VariantGetInt_15f780(src++);
    e->b000_10 = VariantGetInt_15f780(src);
    p->m094 = p->m094 + 1;
    return 1;
}
