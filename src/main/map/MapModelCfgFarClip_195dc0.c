#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;

/* MEASURED (sweep on MapModelCfgWave_195d60, 8 arms): the argument advance only stays
   a real `addiu` when it is a POST-INCREMENT inside the call argument.
   `f(q); q += 8;` -- as a parameter, a separate local, a u8* or an s32*
   -- folds into `addiu $4,$16,K` at the use, and those four spellings are
   ONE object. */

/* `andi $4,$2,0xFF` at the call is the callee's u8 first parameter.
   Stack locals go in REVERSE declaration order, so the 0x3C slot (argument
   two) is declared before the 0x38 slot (argument three). */

extern s32 VariantGetInt_15f780(Arg *);
extern f32 VariantGetFloat_15f740(Arg *);
extern void FarClipRecGetPresetFadeRates_186e70(u8, f32 *, f32 *);

typedef struct Ctx {
    u8 pad000[0x14];
    f32 m14;
    f32 m18;
    s32 m1C;
    f32 m20;
    f32 m24;
} Ctx;

extern Ctx *D_00481328;

s32 MapModelCfgFarClip_195dc0(Arg *p0, s32 p1)
{
    f32 x;
    f32 y;
    f32 a;
    f32 b;
    s32 n;
    s32 k;

    if (D_00481328 == 0) {
        return 0;
    }
    a = VariantGetFloat_15f740(p0++);
    D_00481328->m14 = a;
    n = VariantGetInt_15f780(p0++);
    D_00481328->m1C = n;
    if (p1 >= 3) {
        b = VariantGetFloat_15f740(p0++);
        D_00481328->m18 = b;
    }
    if (p1 >= 5) {
        k = VariantGetInt_15f780(p0);
        FarClipRecGetPresetFadeRates_186e70(k, &x, &y);
        D_00481328->m20 = x;
        D_00481328->m24 = y;
    }
    return 1;
}
