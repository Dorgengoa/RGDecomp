/* rgp:protos */
#define RGP_SELF_MapSceneCfgSkyInfo_192990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;

/* MEASURED (sweep on MapModelCfgWave_195d60, 8 arms): the argument advance only stays
   a real `addiu` when it is a POST-INCREMENT inside the call argument.
   `f(q); q += 8;` -- as a parameter, a separate local, a u8* or an s32*
   -- folds into `addiu $4,$16,K` at the use, and those four spellings are
   ONE object. */

/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Ctx {
    u8 pad000[0x190];
    s32 m190;
    f32 m194;
    f32 m198;
} Ctx;

extern Ctx *D_004812F4;
extern f32 D_0047D1FC;

s32 MapSceneCfgSkyInfo_192990(Arg *p0, s32 p1)
{
    s32 a;
    f32 b;
    f32 c;
    f32 e;

    a = VariantGetInt_15f780(p0++);
    D_004812F4->m190 = a;
    b = VariantGetFloat_15f740(p0++);
    D_004812F4->m194 = b;
    if (p1 >= 3) {
        c = VariantGetFloat_15f740(p0);
        e = WrapAngle_13c050(D_0047D1FC * c / 180.0f);
        D_004812F4->m198 = e;
    }
    return 1;
}
