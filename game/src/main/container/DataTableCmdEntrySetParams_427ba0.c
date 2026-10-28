/* rgp:protos */
#define RGP_SELF_DataTableCmdEntrySetParams_427ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x10];
    s32 f010;
    s32 f014;
    s32 f018;
    s32 f01C[3];
    u8  pad028[0x30];
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
/*rgp*/

s32 DataTableCmdEntrySetParams_427ba0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    e->f010 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f014 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f018 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    for (k0 = 0; k0 < 0x3; k0++) e->f01C[k0] = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    return 1;
}
