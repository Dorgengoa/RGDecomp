/* rgp:protos */
#define RGP_SELF_MapModelCfgType_195e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;
typedef struct Ctx {
    u8 pad000[0x14];
    f32 m14;
    f32 m18;
    s32 m1C;
    f32 m20;
    f32 m24;
} Ctx;

/*rgp*/
extern s32 D_00481310;
extern Ctx *D_00481328;

s32 MapModelCfgType_195e80(Arg *p0, s32 p1)
{
    s32 v;

    if (D_00481328 == 0) {
        return 0;
    }
    v = VariantGetInt_15f780(p0);
    switch (v) {
    case 0:
        v = 0;
        break;
    case 1:
        v = 1;
        break;
    case 2:
        v = 3;
        break;
    case 3:
    case 4:
        D_00481310 = 0;
        v = 4;
        break;
    case 5:
        v = 9;
        break;
    case 6:
        v = 0x10;
        break;
    }
    *(s32 *)((u8 *)D_00481328 + 4) = v;
    return 1;
}
