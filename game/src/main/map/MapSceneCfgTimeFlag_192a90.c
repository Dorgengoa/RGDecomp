/* rgp:protos */
#define RGP_SELF_MapSceneCfgTimeFlag_192a90 1
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

typedef struct Ctx {
    u8 pad000[0x180];
    s32 m180;
    s32 m184;
} Ctx;

extern Ctx *D_004812F4;

s32 MapSceneCfgTimeFlag_192a90(Arg *p0)
{
    s32 a;
    s32 b;

    a = VariantGetInt_15f780(p0++);
    D_004812F4->m180 = a;
    b = VariantGetInt_15f780(p0);
    D_004812F4->m184 = b;
    return 1;
}
