/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_40b860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004;
    s16 f008;
    u8  pad00A[0x2];
    s16 f00C;
    u8  b00E_0 : 1;
    u8  pb00E_1 : 7;
    u8  pad00F[0x19];
} Ent;

typedef struct Lvl1 {
    u8  pad000[0x12];
    s16 cnt012;
    Ent *slots014;
} Lvl1;
typedef struct Lvl0 {
    u8  pad000[0xE];
    s16 cnt00E;
    Lvl1 *slots010;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdSubEntryDefine_40b860(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    Lvl1 *e1;
    s32   n2;
    s32   i2;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt00E;
    if (p->m094 - 1 >= n1) return 1;
    e1 = &e0->slots010[p->m094] - 1;
    n2 = e1->cnt012;
    i2 = p->m098;
    if (i2 >= n2) return 1;
    e = &e1->slots014[i2];
    e->f000 = VariantGetInt_15f780(src++);
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f008 = VariantGetInt_15f780(src++);
    e->f00C = VariantGetInt_15f780(src++);
    e->b00E_0 = VariantGetInt_15f780(src) != 0;
    p->m098 = p->m098 + 1;
    return 1;
}
