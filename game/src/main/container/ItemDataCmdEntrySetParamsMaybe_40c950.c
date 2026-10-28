/* rgp:protos */
#define RGP_SELF_ItemDataCmdEntrySetParamsMaybe_40c950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x2C];
    s16 f02C;
    s16 f02E;
    u8  pad030[0x4];
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

s32 ItemDataCmdEntrySetParamsMaybe_40c950(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    SlotGetInt_15f720(src++);
    e->f02C = VariantGetInt_15f780(src++);
    VariantGetInt_15f780(src++);
    e->f02E = VariantGetInt_15f780(src);
    return 1;
}
