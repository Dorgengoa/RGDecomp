#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;

/* MEASURED (sweep on MapModelCfgWave_195d60, 8 arms): the argument advance only stays
   a real `addiu` when it is a POST-INCREMENT inside the call argument.
   `f(q); q += 8;` -- as a parameter, a separate local, a u8* or an s32*
   -- folds into `addiu $4,$16,K` at the use, and those four spellings are
   ONE object. */

extern f32 VariantGetFloat_15f740(Arg *);

typedef struct Ctx {
    u8 pad000[0x10];
    f32 a;
    f32 b;
    f32 c;
    f32 d;
} Ctx;

extern Ctx *D_00481304;

s32 MapSceneCfgBgColor_193070(Arg *p0)
{
    f32 x;
    f32 y;
    f32 z;

    if (D_00481304 == 0) {
        return 0;
    }
    x = VariantGetFloat_15f740(p0++);
    D_00481304->a = x;
    y = VariantGetFloat_15f740(p0++);
    D_00481304->b = y;
    z = VariantGetFloat_15f740(p0);
    D_00481304->c = z;
    D_00481304->d = 128.0f;
    return 1;
}
