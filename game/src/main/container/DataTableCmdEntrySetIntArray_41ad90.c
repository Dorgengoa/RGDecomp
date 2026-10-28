/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetIntArray_41ad90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x32];
    s16 f032;
    u8  pad034[0x1C];
    u8  f050[5];
    u8  pad055[0x4F];
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

s32 DataTableCmdEntrySetIntArray_41ad90(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    for (k0 = 0; k0 < 0x5; k0++) e->f050[k0] = VariantGetInt_15f780(src++);
    e->f032 = VariantGetInt_15f780(src);
    return 1;
}
