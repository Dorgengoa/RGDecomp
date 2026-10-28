/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_3fd540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    u8  b008_0 : 1;
    u8  b008_1 : 1;
    u8  b008_2 : 1;
    u8  pb008_3 : 5;
    u8  pad009[0x3];
    s32 f00C;
    s32 *f010;
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
/*rgp*/
/*rgp*/

s32 DataTableCmdEntryDefine_3fd540(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32 k;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f000 = VariantGetInt_15f780(src++);
    e->f00C = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f002 = VariantGetInt_15f780(src++);
    e->f004 = VariantGetInt_15f780(src++);
    e->f006 = VariantGetInt_15f780(src++);
    e->b008_0 = 0;
    e->b008_1 = 0;
    e->b008_2 = 0;
    e->f010 = ((s32 *)ArenaAllocWords_3702b0(p->m6C, 0xD, 0x4));
    if (e->f010 != 0) {
        for (k = 0; k < 0xD; k++) e->f010[k] = VariantGetInt_15f780(src++);
    }
    D_004830FC = D_004830FC + 1;
    return 1;
}
