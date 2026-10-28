/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_41b270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  b002_0 : 1;
    u8  pad002_1 : 7;
    u8  pad003;
    s8  b004_0 : 4;
    s8  b004_4 : 4;
    s8  b005_0 : 4;
    s8  b005_4 : 4;
    s16 f006;
    s16 f008;
    u8  pad00A[2];
    s32 f00C;
    s32 f010;
    s32 f014;
    u8  b018_0 : 1;
    u8  pad018_1 : 7;
    u8  pad019[7];
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
/*rgp*/

s32 DataTableCmdEntryDefine_41b270(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 t;
    Ent *e;

    if (n <= 0) return 1;
    if (D_004830FC >= n) return 1;
    t = VariantGetInt_15f780(src++);
    e = &p->slots[D_004830FC];
    e->f000 = t;
    SlotGetInt_15f720(src++);
    e->f008 = VariantGetInt_15f780(src++);
    e->f00C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f010 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f014 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->b002_0 = VariantGetInt_15f780(src++) != 0;
    e->b018_0 = VariantGetInt_15f780(src++) != 0;
    e->b005_0 = (s8)VariantGetInt_15f780(src++);
    e->b004_0 = (s8)VariantGetInt_15f780(src++);
    e->b004_4 = (s8)VariantGetInt_15f780(src++);
    e->f006 = (s32)(1024.0f * VariantGetFloat_15f740(src));
    D_004830FC = D_004830FC + 1;
    return 1;
}
