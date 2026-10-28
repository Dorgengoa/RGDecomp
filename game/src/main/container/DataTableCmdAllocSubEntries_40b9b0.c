/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocSubEntries_40b9b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x12];
    s16 f012;
    s32 f014;
} Ent;

typedef struct Lvl0 {
    u8  pad000[0xE];
    s16 cnt00E;
    Ent *slots010;
} Lvl0;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocSubEntries_40b9b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    Ent  *e;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt00E;
    if (p->m094 - 1 >= n1) return 1;
    e = &e0->slots010[p->m094] - 1;
    t0 = VariantGetInt_15f780(src);
    e->f012 = t0;
    e->f014 = ArenaNew_40bdd0((s16)t0 * 0x28, p->m6C, 0x4, -1);
    p->m098 = 0;
    return 1;
}
