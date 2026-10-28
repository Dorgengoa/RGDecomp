/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_3f8520 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    u8  pad006[0x2];
    s32 f008;
    u8  pad00C[0x38];
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
/*rgp*/

s32 DataTableCmdEntryDefine_3f8520(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  t2;
    s32  t3;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    t2 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f008 = t2;
    t3 = DataTableHashName_368a10(p, t2);
    e->f002 = t3;
    DataTableBitsetClaim_3688b0(p, (u16)t3);
    e->f004 = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
