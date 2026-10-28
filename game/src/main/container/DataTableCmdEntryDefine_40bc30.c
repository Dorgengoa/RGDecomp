/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_40bc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec0 {
    s16 a000;
    s16 a002;
} Rec0;

typedef struct Ent {
    s16 f000;
    Rec0 f002[3];
    u8  pad00E[0x6];
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

s32 DataTableCmdEntryDefine_40bc30(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    for (k0 = 0; k0 < 0x3; k0++) {
        e->f002[k0].a000 = VariantGetInt_15f780(src++);
        e->f002[k0].a002 = VariantGetInt_15f780(src++);
    }
    D_004830FC = D_004830FC + 1;
    return 1;
}
