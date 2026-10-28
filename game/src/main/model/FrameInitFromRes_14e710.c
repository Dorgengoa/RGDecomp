/* rgp:protos */
#define RGP_SELF_FrameInitFromRes_14e710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A_FUN_0014e710 {
    s32 f00;
    u8 pad004[0x20];
    u8 f24;
    u8 pad025[0x7];
    u8 f2C;
} A_FUN_0014e710;

typedef struct B_FUN_0014e710 {
    s32 f00;
    u8 pad004[0x10];
    s32 f14;
    u8 pad018[0x7];
    u8 f1F;
    u8 f20;
} B_FUN_0014e710;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void FrameInitFromRes_14e710(A_FUN_0014e710 *a, B_FUN_0014e710 *b, s32 c)
{
    a->f00 = ((s32)MemStackStrDup_14cf10(b->f00, c));
    ModelFrameSetMatrix_14a190(a, &b->f20);
    Mat44To34_13e270((u8 *)a + 0x30, &b->f20);
    a->f2C = 1;
    a->f24 = b->f1F;
    ModelFrameSetFlags_14a760(a, b->f14);
}
