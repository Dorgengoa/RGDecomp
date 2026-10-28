/* rgp:protos */
#define RGP_SELF_ItemDataCmdSetPrices_40d4a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x1A];
    s16 f01A;
    s16 f01C;
    u8  f01E;
    s8  b01F_0 : 1;
    s8  pb01F_1 : 7;
    u8  pad020[0x14];
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

s32 ItemDataCmdSetPrices_40d4a0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f01A = VariantGetInt_15f780(src++);
    e->f01C = VariantGetInt_15f780(src++);
    e->b01F_0 = (s8)VariantGetInt_15f780(src++);
    e->f01E = VariantGetInt_15f780(src);
    return 1;
}
