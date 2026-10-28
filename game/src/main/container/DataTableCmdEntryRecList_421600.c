/* rgp:protos */
#define RGP_SELF_DataTableCmdEntryRecList_421600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Sub0 {
    s16 f000;
    s16 f002;
    f32 f004;
    f32 f008;
    f32 f00C;
} Sub0;

typedef struct Ent {
    u8  pad000[0xA];
    s16 f00A;
    Sub0 *f00C;
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

s32 DataTableCmdEntryRecList_421600(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    Sub0 *w0;
    s32  k0;
    s32  t0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = &p->slots[i];
    t0 = VariantGetInt_15f780(src++);
    e->f00A = t0;
    if ((s16)t0 > 0) e->f00C = ArenaNew_4235b0((s16)t0 * 0x10, p->m6C, 0x4, -1);
    else e->f00C = 0;
    w0 = e->f00C;
    for (k0 = 0; k0 < e->f00A; k0++) {
        w0->f000 = VariantGetInt_15f780(src++);
        w0->f002 = VariantGetInt_15f780(src++);
        w0->f004 = VariantGetFloat_15f740(src++);
        w0->f008 = VariantGetFloat_15f740(src++);
        w0->f00C = VariantGetFloat_15f740(src++);
        w0++;
    }
    return 1;
}
