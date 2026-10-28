/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_424b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  pad002[0x2];
    s32 f004;
    s16 f008;
    u8  pad00A[0x6];
} Ent;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Ent *slots;
    u8   pad090[0xC];
    s16  m09C;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern u8    D_00483F14;
/*rgp*/
/*rgp*/
/*rgp*/

s32 DataTableCmdEntryDefine_424b70(R8 *src)
{
    Pool *p = D_004830F8;
    s32   t;
    Ent  *e;

    if (p->count <= 0) return 1;
    D_00483F14 = 0;
    if (D_004830FC >= p->count) {
        D_00483F14 = 1;
        return 1;
    }
    t = VariantGetInt_15f780(src++);
    if (p->m09C >= 0 && p->m09C != t) {
        D_00483F14 = 1;
        return 1;
    }
    e = &p->slots[D_004830FC];
    e->f000 = t;
    e->f004 = DataTableStoreString_368ab0(p, SlotGetInt_15f720(src++));
    e->f008 = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
