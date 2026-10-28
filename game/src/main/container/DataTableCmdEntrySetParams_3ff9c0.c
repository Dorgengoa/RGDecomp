/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_3ff9c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x2];
    s16 f002;
    s16 f004;
    u8  pad006[0x12];
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

s32 DataTableCmdEntrySetParams_3ff9c0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src);
    return 1;
}
