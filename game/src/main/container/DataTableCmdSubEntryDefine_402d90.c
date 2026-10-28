/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_402d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Lvl0 Lvl0;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s16 f004;
    s16 f006;
    f32 f008;
    f32 f00C;
    f32 f010;
    f32 f014;
    Lvl0 *f018;
} Ent;

struct Lvl0 {
    u8  pad000[0x7C];
    s8  b07C_0 : 5;
    s8  pb07C_5 : 3;
    u8  pad07D[0x3];
    Ent *slots080;
    u8  pad084[0xC];
};

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x4];
    s32  m094;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/

s32 DataTableCmdSubEntryDefine_402d90(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    Ent *q1;
    s32   n1;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    q1 = e0->slots080;
    if (q1 == 0) return 1;
    n1 = e0->b07C_0;
    if (n1 <= 0) return 1;
    if (p->m094 - 1 >= n1) return 1;
    e = &q1[p->m094];
    e->f004 = VariantGetInt_15f780(src++);
    e->f000 = VariantGetInt_15f780(src++);
    e->f018 = e0;
    e->f006 = VariantGetFloat_15f740(src++);
    e->f008 = VariantGetFloat_15f740(src++);
    e->f00C = VariantGetFloat_15f740(src++);
    e->f010 = VariantGetFloat_15f740(src++);
    e->f014 = VariantGetFloat_15f740(src);
    p->m094 = p->m094 + 1;
    return 1;
}
