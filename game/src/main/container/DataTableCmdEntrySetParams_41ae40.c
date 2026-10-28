/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_41ae40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x28];
    s16 f028;
    s16 f02A;
    s16 f02C;
    s16 f02E;
    s16 f030;
    u8  pad032[0x2];
    f32 f034;
    f32 f038;
    f32 f03C;
    f32 f040;
    f32 f044;
    f32 f048;
    f32 f04C;
    u8  pad050[0x54];
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

s32 DataTableCmdEntrySetParams_41ae40(R8 *src)
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
    e->f028 = VariantGetInt_15f780(src++);
    e->f02A = VariantGetInt_15f780(src++);
    e->f02E = VariantGetInt_15f780(src++);
    e->f030 = VariantGetInt_15f780(src++);
    e->f034 = VariantGetFloat_15f740(src++);
    e->f038 = VariantGetFloat_15f740(src++);
    e->f03C = VariantGetFloat_15f740(src++);
    e->f040 = VariantGetFloat_15f740(src++);
    e->f044 = VariantGetFloat_15f740(src++);
    e->f048 = VariantGetFloat_15f740(src++);
    e->f04C = VariantGetFloat_15f740(src);
    return 1;
}
