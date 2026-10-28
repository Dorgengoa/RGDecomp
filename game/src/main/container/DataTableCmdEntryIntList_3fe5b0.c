/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryIntList_3fe5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x48];
    s16 f048;
    u8  pad04A[0x2];
    s16 *f04C;
    u8  pad050[0x8];
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

s32 DataTableCmdEntryIntList_3fe5b0(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src++);
    e->f048 = t0;
    if ((s16)t0 > 0) e->f04C = ArenaNew_3ff030((s16)t0 * 0x2, p->m6C, 0x4, -1);
    else e->f04C = 0;
    if (e->f04C != 0) {
        for (k0 = 0; k0 < e->f048; k0++) e->f04C[k0] = VariantGetInt_15f780(src++);
    }
    return 1;
}
