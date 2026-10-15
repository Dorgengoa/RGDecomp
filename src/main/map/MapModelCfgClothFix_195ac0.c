#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;

/* MEASURED (sweep on MapModelCfgWave_195d60, 8 arms): the argument advance only stays
   a real `addiu` when it is a POST-INCREMENT inside the call argument.
   `f(q); q += 8;` -- as a parameter, a separate local, a u8* or an s32*
   -- folds into `addiu $4,$16,K` at the use, and those four spellings are
   ONE object. */

extern s32 VariantGetInt_15f780(Arg *);
extern void ClothPinVertex_1854c0(void *, s32);

extern void *D_00481354;

s32 MapModelCfgClothFix_195ac0(Arg *p0, s32 p1)
{
    s32 i;
    s32 v;

    if (D_00481354 == 0) {
        return 0;
    }
    for (i = 0; i < p1; i++) {
        v = VariantGetInt_15f780(p0++);
        ClothPinVertex_1854c0(D_00481354, v);
    }
    return 1;
}
