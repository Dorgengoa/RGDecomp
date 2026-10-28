/* rgp:protos */
#define RGP_SELF_MapSceneCfgFog_192bb0 1
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
    f32 m1A4;
    f32 m1A8;
    u8 m1AC;
    u8 m1AD;
    u8 m1AE;
    u8 pad1AF[0x9];
    f32 m1B8;
    f32 m1BC;
} Ctx;

extern Ctx *D_00481304;

/* Both guards are `> K-1`, not `>= K`: the branch-taken condition is then
   `<=`, which is the [[at-compare-class]] cell that lands the `slti` in $at.
   The `>= K` spelling emits the same slti into $2/$3 and is 6 words wrong. */

s32 MapSceneCfgFog_192bb0(Arg *p0, s32 p1)
{
    f32 a;
    f32 b;
    s32 c;
    s32 e;
    s32 f;
    f32 g;
    f32 h;

    if (D_00481304 == 0) {
        return 0;
    }
    D_00481304->m1AC = 0xFF;
    D_00481304->m1AD = 0xFF;
    D_00481304->m1AE = 0xFF;
    D_00481304->m1B8 = 0.0f;
    D_00481304->m1BC = 255.0f;
    a = VariantGetFloat_15f740(p0++);
    D_00481304->m1A4 = a;
    b = VariantGetFloat_15f740(p0++);
    D_00481304->m1A8 = b;
    if (p1 > 2) {
        c = VariantGetInt_15f780(p0++);
        D_00481304->m1AC = c;
        e = VariantGetInt_15f780(p0++);
        D_00481304->m1AD = e;
        f = VariantGetInt_15f780(p0++);
        D_00481304->m1AE = f;
    }
    if (p1 > 5) {
        g = VariantGetFloat_15f740(p0++);
        D_00481304->m1B8 = g;
        h = VariantGetFloat_15f740(p0);
        D_00481304->m1BC = h;
    }
    return 1;
}
