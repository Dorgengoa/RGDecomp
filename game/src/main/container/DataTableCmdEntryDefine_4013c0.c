/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryDefine_4013c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    s16 f000;
    u8  b002_0 : 1;
    u8  pb002_1 : 7;
    u8  pad003[0x2D];
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

s32 DataTableCmdEntryDefine_4013c0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    Ent *e;
    s32  t0;

    if (n <= 0) return 1;
    if (D_004830FC >= n) return 1;
    t0 = VariantGetInt_15f780(src++);
    e = &p->slots[D_004830FC];
    e->f000 = t0;
    SlotGetInt_15f720(src);
    e->b002_0 = 0;
    D_004830FC = D_004830FC + 1;
    return 1;
}
