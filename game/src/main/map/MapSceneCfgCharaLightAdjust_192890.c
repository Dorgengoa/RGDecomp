/* rgp:protos */
#define RGP_SELF_MapSceneCfgCharaLightAdjust_192890 1
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

typedef struct Ctx {
    u8 pad000[0x1A4];
    s32 m1A4;
    f32 m1A8;
    f32 m1AC;
    f32 m1B0;
} Ctx;

extern Ctx *D_004812F4;

s32 MapSceneCfgCharaLightAdjust_192890(Arg *p0)
{
    s32 a;
    f32 b;
    f32 c;
    f32 e;

    a = VariantGetInt_15f780(p0++);
    D_004812F4->m1A4 = a;
    b = VariantGetFloat_15f740(p0++);
    D_004812F4->m1A8 = b;
    c = VariantGetFloat_15f740(p0++);
    D_004812F4->m1AC = c;
    e = VariantGetFloat_15f740(p0);
    D_004812F4->m1B0 = e;
    return 1;
}
