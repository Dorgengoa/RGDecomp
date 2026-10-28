/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_400ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x26];
    s16 f026;
    s16 f028;
    s16 f02A;
    s16 f02C;
    u8  pad02E[0x6];
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

s32 DataTableCmdEntrySetParams_400ce0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f026 = VariantGetInt_15f780(src++);
    e->f028 = VariantGetInt_15f780(src++);
    e->f02A = VariantGetInt_15f780(src++);
    e->f02C = VariantGetInt_15f780(src);
    return 1;
}
