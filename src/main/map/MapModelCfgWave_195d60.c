#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;

/* MEASURED (sweep on MapModelCfgWave_195d60, 8 arms): the argument advance only stays
   a real `addiu` when it is a POST-INCREMENT inside the call argument.
   `f(q); q += 8;` -- as a parameter, a separate local, a u8* or an s32*
   -- folds into `addiu $4,$16,K` at the use, and those four spellings are
   ONE object. */

extern f32 VariantGetFloat_15f740(Arg *);

extern s32 D_00481338;
extern f32 D_00481340;
extern f32 D_00481344;
extern f32 D_00481348;

s32 MapModelCfgWave_195d60(Arg *p0)
{
    f32 a;
    f32 b;
    f32 c;

    D_00481338 = 1;
    a = VariantGetFloat_15f740(p0++);
    D_00481340 = a;
    b = VariantGetFloat_15f740(p0++);
    D_00481344 = b;
    c = VariantGetFloat_15f740(p0);
    D_00481348 = c;
    return 1;
}
