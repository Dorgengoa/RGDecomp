/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_41a460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x86];
    s16 f086;
    s16 f088;
    s16 f08A;
    s16 f08C;
    s16 f08E;
    u8  pad090[0x14];
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

s32 DataTableCmdEntrySetParams_41a460(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f086 = VariantGetInt_15f780(src++);
    e->f088 = VariantGetInt_15f780(src++);
    e->f08A = VariantGetInt_15f780(src++);
    e->f08C = (s32)(60.0f * VariantGetFloat_15f740(src++));
    e->f08E = VariantGetInt_15f780(src);
    return 1;
}
