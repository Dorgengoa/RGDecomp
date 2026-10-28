/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_3febe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xE];
    s16 f00E;
    s16 f010;
    s16 f012;
    s16 f014;
    s16 f016;
    s16 f018;
    s16 f01A;
    s16 f01C;
    s16 f01E;
    u8  pad020[0x38];
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

s32 DataTableCmdEntrySetParams_3febe0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f00E = VariantGetInt_15f780(src++);
    e->f010 = VariantGetInt_15f780(src++);
    e->f012 = VariantGetInt_15f780(src++);
    e->f014 = VariantGetInt_15f780(src++);
    e->f016 = VariantGetInt_15f780(src++);
    e->f018 = VariantGetInt_15f780(src++);
    e->f01A = VariantGetInt_15f780(src++);
    e->f01C = VariantGetInt_15f780(src++);
    e->f01E = VariantGetInt_15f780(src);
    return 1;
}
