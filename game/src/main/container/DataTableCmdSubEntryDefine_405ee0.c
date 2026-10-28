/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_405ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  b002_0 : 1;
    u8  pb002_1 : 7;
    u8  pad003[0x1];
    s32 f004;
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x6];
    s16 cnt006;
    Ent *slots008;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/
extern s32  D_00483C54;

s32 DataTableCmdSubEntryDefine_405ee0(R8 *src)
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
    n1 = e0->cnt006;
    i1 = D_00483C54;
    if (i1 >= n1) return 1;
    e = &e0->slots008[i1];
    e->f000 = VariantGetInt_15f780(src++);
    e->b002_0 = VariantGetInt_15f780(src++) != 0;
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src));
    D_00483C54 = D_00483C54 + 1;
    return 1;
}
