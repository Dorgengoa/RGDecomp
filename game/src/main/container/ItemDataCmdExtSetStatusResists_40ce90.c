/* rgp:protos */
#define RGP_SELF_ItemDataCmdExtSetStatusResists_40ce90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Ent {
    u8  pad000[0x9];
    u8  f009[8];
} Ent;

typedef struct Hdr { u8 b[0x34]; } Hdr;

typedef struct Pool {
    u8   pad000[0x7C];
    s16  count;
    u8   pad07E[0xE];
    Hdr *slots;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
/*rgp*/
/*rgp*/

s32 ItemDataCmdExtSetStatusResists_40ce90(R8 *src)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;
    Ent *e;
    s32  k0;

    if (n <= 0) return 1;
    i = D_004830FC - 1;
    if (i >= n) return 1;
    e = ((Ent *)ItemDefGetKind2Or3Data_40e140(&p->slots[i]));
    if (e == 0) return 1;
    for (k0 = 0; k0 < 0x8; k0++) e->f009[k0] = VariantGetInt_15f780(src++);
    return 1;
}
