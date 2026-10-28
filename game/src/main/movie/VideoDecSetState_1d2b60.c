/* rgp:protos */
#define RGP_SELF_VideoDecSetState_1d2b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d2b60 {
    u8 pad000[0xA8];
    s32 mA8;         /* +0xA8 */
} Obj_FUN_001d2b60;

s32 VideoDecSetState_1d2b60(Obj_FUN_001d2b60 *o, s32 p1)
{
    s32 oldA8;

    oldA8 = o->mA8;
    o->mA8 = p1;
    return oldA8;
}
