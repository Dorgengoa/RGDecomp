/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_41a1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
} Ent;

typedef struct Lvl0 {
    u8  pad000[0x9A];
    s16 cnt09A;
    Ent *slots09C;
    u8  pad0A0[0x4];
} Lvl0;

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

s32 DataTableCmdSubEntryDefine_41a1a0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Lvl0 *e0;
    s32   n1;
    s32   i1;
    Ent  *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e0 = &p->slots[i];
    n1 = e0->cnt09A;
    i1 = p->m094;
    if (i1 >= n1) return 1;
    e = &e0->slots09C[i1];
    e->f000 = VariantGetInt_15f780(src++);
    SlotGetInt_15f720(src++);
    SlotGetInt_15f720(src++);
    e->f002 = VariantGetInt_15f780(src);
    p->m094 = p->m094 + 1;
    return 1;
}
