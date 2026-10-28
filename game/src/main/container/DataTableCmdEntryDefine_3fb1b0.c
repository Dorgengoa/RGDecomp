/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_3fb1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x6];
    s8  b008_0 : 5;
    s8  b008_5 : 3;
    s8  b009_0 : 6;
    s8  pb009_6 : 2;
    u8  pad00A[0x2];
    s32 f00C;
    u8  pad010[0x4];
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

s32 DataTableCmdEntryDefine_3fb1b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b009_0 = 0;
    e->f00C = 0;
    e->f000 = VariantGetInt_15f780(src++);
    SlotGetInt_15f720(src++);
    e->b008_0 = (s8)VariantGetInt_15f780(src++);
    e->b008_5 = (s8)VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
