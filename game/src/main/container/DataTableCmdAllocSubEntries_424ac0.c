/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocSubEntries_424ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0xA];
    s16 f00A;
    s32 f00C;
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
extern s32  D_00483F10;
extern u8   D_00483F14;

s32 DataTableCmdAllocSubEntries_424ac0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n;
    s32 i;
    Ent *e;
    s32  t0;

    if (D_00483F14 != 0) return 1;
    n = p->count;
    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src);
    e->f00A = t0;
    if ((s16)t0 > 0) e->f00C = ArenaNew_424f40((s16)t0 * 0xC, p->m6C, 0x4, -1);
    else e->f00C = 0;
    D_00483F10 = 0;
    return 1;
}
