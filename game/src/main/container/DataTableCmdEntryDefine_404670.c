/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_404670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x6];
    s16 f008;
    s16 f00A;
    s32 f00C;
    s8  b010_0 : 4;
    s8  b010_4 : 4;
    s8  b011_0 : 4;
    s8  b011_4 : 4;
    s8  b012_0 : 4;
    s8  b012_4 : 4;
    u8  pad013[0xD];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdEntryDefine_404670(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    e->f00C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f008 = VariantGetInt_15f780(src++);
    e->f00A = VariantGetInt_15f780(src++);
    e->b010_0 = (s8)VariantGetInt_15f780(src++);
    e->b010_4 = (s8)VariantGetInt_15f780(src++);
    e->b011_0 = (s8)VariantGetInt_15f780(src++);
    e->b011_4 = (s8)VariantGetInt_15f780(src++);
    e->b012_0 = (s8)VariantGetInt_15f780(src++);
    e->b012_4 = (s8)VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
