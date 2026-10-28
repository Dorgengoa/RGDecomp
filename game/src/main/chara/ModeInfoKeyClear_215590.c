/* rgp:protos */
#define RGP_SELF_ModeInfoKeyClear_215590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00215590 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_00215590;

Obj_FUN_00215590 * ModeInfoKeyClear_215590(Obj_FUN_00215590 *o)
{
    o->m00 = -1;
    o->m04 = -1;
    o->m08 = 0;
    return o;
}
