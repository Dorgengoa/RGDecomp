/* rgp:protos */
#define RGP_SELF_DynClothSetFloor_1693f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001693f0 {
    u8 pad000[0x148];
    s32 m148;         /* +0x148 */
    f32 m14C;         /* +0x14C */
} Obj_FUN_001693f0;

void DynClothSetFloor_1693f0(Obj_FUN_001693f0 *o, f32 fa0)
{
    o->m148 = 1;
    o->m14C = fa0;
}
