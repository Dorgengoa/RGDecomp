#include "types.h"

/* clone group cg06-006: signed-halfword range test against two NON-gp globals
   (declared as arrays so mwcc keeps them out of .sdata).  Members differ only
   in the pair of bound symbols. */

typedef struct Rec {
    u8 pad00[6];
    s16 f06;
} Rec;

extern s32 D_00465A38[4];
extern s32 D_00465A40[4];

u8 ItemInInvCategory1_3d4920(Rec *r)
{
    s16 v;
    u8 ok;

    ok = 0;
    v = r->f06;
    if (v >= D_00465A38[0] && v <= D_00465A40[0]) {
        ok = 1;
    }
    return ok;
}
