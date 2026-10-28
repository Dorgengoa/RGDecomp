/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_3f7220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  f002;
    u8  f003;
    u8  f004;
    u8  f005[6];
    u8  pad00B[0x1];
    s16 f00C;
    u8  f00E;
    u8  f00F;
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

s32 DataTableCmdEntryDefine_3f7220(R8 *src)
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
    SlotGetInt_15f720(src++);
    e->f002 = VariantGetInt_15f780(src++);
    e->f003 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    for (k0 = 0; k0 < 0x6; k0++) e->f005[k0] = VariantGetInt_15f780(src++);
    e->f00C = VariantGetInt_15f780(src++);
    e->f00E = VariantGetInt_15f780(src++);
    e->f00F = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
