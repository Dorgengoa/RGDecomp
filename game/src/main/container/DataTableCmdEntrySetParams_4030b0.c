/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_4030b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x2C];
    s16 f02C;
    u8  pad02E[0x2];
    u8  b030_0 : 1;
    u8  pb030_1 : 7;
    u8  pad031[0x3];
    f32 f034;
    f32 f038;
    f32 f03C;
    u8  pad040[0x50];
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

s32 DataTableCmdEntrySetParams_4030b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f02C = VariantGetInt_15f780(src++);
    e->b030_0 = VariantGetInt_15f780(src++) != 0;
    e->f034 = VariantGetFloat_15f740(src++);
    e->f038 = VariantGetFloat_15f740(src++);
    e->f03C = VariantGetFloat_15f740(src);
    return 1;
}
