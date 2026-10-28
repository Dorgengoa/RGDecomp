/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_427970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s16 f004;
    u8  pad006[0x2];
    s16 f008;
    s16 f00A;
    u8  pad00C[0x30];
    s32 f03C;
    u8  pad040[0x4];
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

s32 DataTableCmdEntryDefine_427970(R8 *src)
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
    e->f004 = VariantGetInt_15f780(src++);
    e->f008 = VariantGetInt_15f780(src++);
    e->f00A = VariantGetInt_15f780(src);
    e->f03C = 0;
    TreasureBoxParamRowClearRuntimeMaybe_427ef0(e);
    D_004830FC = D_004830FC + 1;
    return 1;
}
