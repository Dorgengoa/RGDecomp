/* rgp:protos */
#define RGP_SELF_EffAttachIntegrateRot_1979c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8  pad000[0x4];
    s32 m04;
} A;

typedef struct B {
    u8  pad000[0xB4];
    u8 *mB4;
} B;

/*rgp*/

void EffAttachIntegrateRot_1979c0(A *a, B *b, f32 t)
{
    u8 *p;

    p = b->mB4 + a->m04 * 16;
    VecAddScaled_13bdd0((u8 *)b + 0x20, p, t);
    VecAddScaled_13bdd0(p, p + 0x10, t);
}
