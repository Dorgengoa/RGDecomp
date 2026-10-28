/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_4148a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s32 a;
    s32 b;
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

s32 DataTableCmdEntryDefine_4148a0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;

    if (n <= 0) {
        return 1;
    }
    i = D_004830FC;
    if (i >= n) {
        return 1;
    }
    e = &p->slots[i];
    e->a = VariantGetInt_15f780(src++);
    e->b = VariantGetInt_15f780(src);
    D_004830FC = D_004830FC + 1;
    return 1;
}
