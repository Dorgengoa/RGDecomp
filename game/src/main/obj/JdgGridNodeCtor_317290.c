/* rgp:protos */
#define RGP_SELF_JdgGridNodeCtor_317290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00317290 {
    u8 pad000[0x24];
    s32 m24;         /* +0x24 */
} Obj_FUN_00317290;

Obj_FUN_00317290 * JdgGridNodeCtor_317290(Obj_FUN_00317290 *o)
{
    o->m24 = 0;
    return o;
}
