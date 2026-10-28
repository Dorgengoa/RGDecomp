/* rgp:protos */
#define RGP_SELF_MesWinAddShownEnd_271670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00271670 {
    u8 pad000[0xBC];
    s32 mBC;         /* +0xBC */
} Obj_FUN_00271670;

void MesWinAddShownEnd_271670(Obj_FUN_00271670 *o, s32 p1)
{
    o->mBC = (o->mBC + p1);
}
