/* rgp:protos */
#define RGP_SELF_DataTableCmdStateFlagDefine_421c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004;
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
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
/*rgp*/

s32 DataTableCmdStateFlagDefine_421c90(R8 *src)
{
    Pool *p = D_004830F8;
    s32   t0;
    s8   *t1;
    s32   t2;
    s32   n;
    s32   i;
    Ent  *e;

    t0 = VariantGetInt_15f780(src++);
    t1 = ((s8 *)SlotGetInt_15f720(src++));
    t2 = VariantGetInt_15f780(src);
    if (p->m094 != 0) StateFlag2SetQuiet_3cc7d0(p->m094, t0, t2 != 0);
    if (t0 < 0 || t0 >= 0x800) return 1;
    if (t1 == 0) return 1;
    if (*t1 == 0) return 1;
    if (p->slots == 0) return 1;
    n = p->count;
    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = t0;
    e->f004 = DataTableStoreString_368ab0(p, t1);
    D_004830FC = D_004830FC + 1;
    return 1;
}
