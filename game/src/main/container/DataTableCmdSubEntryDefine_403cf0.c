/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_403cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s16 f004;
    u8  pad006[0x2];
    void *f008;
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x2C];
    s8  cnt02C;
    u8  pad02D[0x3];
    Ent *slots030;
    u8  pad034[0x8];
} Lvl0;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Lvl0 *slots;
    u8   pad090[0x8];
    s32  m098;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/

s32 DataTableCmdSubEntryDefine_403cf0(R8 *src)
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
    q1 = e0->slots030;
    if (q1 == 0) return 1;
    n1 = e0->cnt02C;
    if (n1 <= 0) return 1;
    if (p->m098 - 1 >= n1) return 1;
    e = &q1[p->m098];
    e->f000 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src);
    e->f008 = e0;
    p->m098 = p->m098 + 1;
    return 1;
}
