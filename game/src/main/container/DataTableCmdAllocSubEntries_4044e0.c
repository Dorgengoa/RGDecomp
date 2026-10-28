/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocSubEntries_4044e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x16];
    s8  b016_0 : 4;
    s8  pb016_4 : 4;
    u8  pad017[0x1];
    s32 f018;
    u8  pad01C[0x4];
} Ent;

typedef struct Pool {
    u8   pad000[0x6C];
    u8   m6C[0x10];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/

s32 DataTableCmdAllocSubEntries_4044e0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->b016_0 = (s8)VariantGetInt_15f780(src);
    if (e->b016_0 > 0) e->f018 = ArenaNew_4049f0(e->b016_0 * 0xC, p->m6C, 0x4, -1);
    else e->f018 = 0;
    p->m094 = 0;
    return 1;
}
