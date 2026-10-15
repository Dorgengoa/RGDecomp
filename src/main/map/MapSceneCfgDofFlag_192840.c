#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;

/* MEASURED (sweep on MapModelCfgWave_195d60, 8 arms): the argument advance only stays
   a real `addiu` when it is a POST-INCREMENT inside the call argument.
   `f(q); q += 8;` -- as a parameter, a separate local, a u8* or an s32*
   -- folds into `addiu $4,$16,K` at the use, and those four spellings are
   ONE object. */

extern s32 VariantGetInt_15f780(Arg *);

typedef struct Ctx {
    u8 pad000[0x1B4];
    s32 m1B4;
    s32 m1B8;
} Ctx;

extern Ctx *D_004812F4;

s32 MapSceneCfgDofFlag_192840(Arg *p0)
{
    s32 a;
    s32 b;

    a = VariantGetInt_15f780(p0++);
    D_004812F4->m1B4 = a;
    b = VariantGetInt_15f780(p0);
    D_004812F4->m1B8 = b;
    return 1;
}
