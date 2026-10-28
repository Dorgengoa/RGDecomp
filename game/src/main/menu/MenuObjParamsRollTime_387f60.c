/* rgp:protos */
#define RGP_SELF_MenuObjParamsRollTime_387f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S387 {
    u8  pad000[0x10];
    s32 mA;
    s32 mB;
    u8  padC[0x24 - (0x10 + 8)];
    s32 mC;
} S387;

/*rgp*/

void MenuObjParamsRollTime_387f60(S387 *p)
{
    s32 a;
    s32 d;
    f32 t;

    a = p->mA;
    t = RandFloat_13c010();
    d = p->mB - a;
    p->mC = (s32)((f32)a + (f32)d * t);
}
