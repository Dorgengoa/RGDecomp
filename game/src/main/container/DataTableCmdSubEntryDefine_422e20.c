/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_422e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x6];
    s16 f008;
    u8  pad00A[0x2];
    s32 f00C;
    s32 f010;
    u8  pad014[0xC];
} Ent;

typedef struct Lvl0 {
    u8   pad000[0x14];
    s32  cnt014;
    Ent *slots018;
    u8   pad01C[0x4];
} Lvl0;

typedef struct Pool {
    u8    pad000[0x7C];
    s16   count;
    u8    pad07E[0xE];
    Lvl0 *slots;
    u8    pad090[0x2C];
    s32   m0BC;
    s32   m0C0;
    u8    pad0C4[0x4];
    s32   m0C8;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdSubEntryDefine_422e20(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32 n1;
    Ent *e;
    s32 t;
    s32 m;
    void *q;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    if (e0->slots018 == 0) return 1;
    n1 = e0->cnt014;
    if (n1 <= 0) return 1;
    if (p->m0BC >= n1) return 1;
    e = &e0->slots018[p->m0BC];
    t = VariantGetInt_15f780(src++);
    m = p->m0C8;
    q = SlotGetInt_15f720(src);
    if (m < 0 || m >= 0xF) return 1;
    e->f000 = t;
    e->f008 = m;
    e->f00C = DataTableStoreString_368ab0(p, q);
    e->f010 = 0;
    p->m0BC = p->m0BC + 1;
    p->m0C0 = 0;
    p->m0C8 = p->m0C8 + 1;
    return 1;
}
