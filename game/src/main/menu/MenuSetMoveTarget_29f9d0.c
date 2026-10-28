/* rgp:protos */
#define RGP_SELF_MenuSetMoveTarget_29f9d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0029f9d0 {
    u8 pad000[0xEC];
    s32 mEC;         /* +0xEC */
    s32 mF0;         /* +0xF0 */
} Obj_FUN_0029f9d0;

s32 MenuSetMoveTarget_29f9d0(Obj_FUN_0029f9d0 *o, s32 p1, s32 p2)
{
    o->mEC = p1;
    o->mF0 = p2;
    return 1;
}
