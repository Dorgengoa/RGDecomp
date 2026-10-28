/* rgp:protos */
#define RGP_SELF_MenuObjParamsRollCountMaybe_387ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S387 {
    u8  pad000[0x18];
    s32 mA;
    s32 mB;
    u8  padC[0x28 - (0x18 + 8)];
    s32 mC;
} S387;

/*rgp*/

void MenuObjParamsRollCountMaybe_387ef0(S387 *p)
{
    s32 a;
    s32 d;
    f32 t;

    a = p->mA;
    t = RandFloat_13c010();
    d = p->mB - a;
    p->mC = (s32)((f32)a + (f32)d * t);
}
