/* rgp:protos */
#define RGP_SELF_MapModelCfgModelRm_195cd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg { s32 w[2]; } Arg;

/* MEASURED (sweep on MapModelCfgWave_195d60, 8 arms): the argument advance only stays
   a real `addiu` when it is a POST-INCREMENT inside the call argument.
   `f(q); q += 8;` -- as a parameter, a separate local, a u8* or an s32*
   -- folds into `addiu $4,$16,K` at the use, and those four spellings are
   ONE object. */

/* `addiu $4,$28,%gp_rel(D_00481310)` is the ADDRESS of a small-data global,
   so the declaration stays <= 8 bytes and the source takes `&`. */

/*rgp*/

typedef struct Ent {
    u8 pad000[0xC];
    s32 m0C;
} Ent;

typedef struct Iter {
    u8 pad000[0x20];
} Iter;

/*rgp*/
extern void ModelResGetMeshInfo_14c440(Iter *, void *, s32);
/*rgp*/
/*rgp*/

extern s32 D_00481310;

s32 MapModelCfgModelRm_195cd0(Arg *p0, s32 p1)
{
    s32 i;
    s32 v;
    Ent *e;
    s32 t;
    Iter it __attribute__((aligned(16)));

    for (i = 0; i < p1; i++) {
        v = SlotGetInt_15f720(p0++);
        e = ((Ent *)ModelResFindFrameByName_14c660(&D_00481310, v));
        if (e != 0) {
            ModelResGetMeshInfo_14c440(&it, &D_00481310, e->m0C);
            t = ModelResGetMeshClass_14cea0(&it);
            ModelResSetMeshClass_14ce80(&it, t | 1);
        }
    }
    return 1;
}
