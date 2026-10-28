/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryIntList_408e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Sub0 {
    s16 f000;
    u8  pad002[0x2];
} Sub0;

typedef struct Ent {
    u8  pad000[0xC];
    s16 f00C;
    u8  pad00E[0x2];
    Sub0 *f010;
    u8  pad014[0x4];
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

s32 DataTableCmdEntryIntList_408e20(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src++);
    e->f00C = t0;
    if ((s16)t0 > 0) e->f010 = ArenaNew_409ec0((s16)t0 * 0x4, p->m6C, 0x4, -1);
    else e->f010 = 0;
    for (k0 = 0; k0 < e->f00C; k0++) e->f010[k0].f000 = VariantGetInt_15f780(src++);
    return 1;
}
