/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_3f4db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x20];
    f32 f020;
    f32 f024;
    u8  pad028[0x4];
    f32 f02C;
    f32 f030;
    f32 f034;
    f32 f038;
    u8  pad03C[0x4];
    s16 f040;
    s16 f042;
    u8  pad044[0x4];
    u8  f048;
    u8  f049;
    u8  b04A_0 : 1;
    u8  pb04A_1 : 7;
} Ent;

typedef struct Hdr { u8 b[0x1C]; } Hdr;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Hdr *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdEntrySetParams_3f4db0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = ((Ent *)AbilityDataGetKind0Rec_3f5db0(&p->slots[i]));
    if (e == 0) return 1;
    VariantGetInt_15f780(src++);
    VariantGetFloat_15f740(src++);
    e->f020 = VariantGetFloat_15f740(src++);
    e->f02C = VariantGetFloat_15f740(src++);
    e->f030 = VariantGetFloat_15f740(src++);
    e->f034 = VariantGetFloat_15f740(src++);
    e->f038 = VariantGetFloat_15f740(src++);
    e->f024 = VariantGetFloat_15f740(src++);
    e->f040 = VariantGetInt_15f780(src++);
    e->f042 = VariantGetInt_15f780(src++);
    e->f048 = VariantGetInt_15f780(src++);
    e->f049 = VariantGetInt_15f780(src++);
    e->b04A_0 = VariantGetInt_15f780(src) != 0;
    return 1;
}
