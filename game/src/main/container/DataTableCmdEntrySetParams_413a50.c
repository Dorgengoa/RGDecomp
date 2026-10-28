/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_413a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x10];
    f32 f010;
    f32 f014;
    f32 f018;
    f32 f01C;
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

s32 DataTableCmdEntrySetParams_413a50(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f010 = VariantGetFloat_15f740(src++);
    e->f014 = VariantGetFloat_15f740(src++);
    e->f018 = VariantGetFloat_15f740(src++);
    e->f01C = VariantGetFloat_15f740(src);
    return 1;
}
