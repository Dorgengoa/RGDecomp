/* rgp:protos */
#define RGP_SELF_NodeSetEnabled_18bbc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0018bbc0 {
    u8 pad000[0x32];
    s16 m32;         /* +0x32 */
} Obj_FUN_0018bbc0;

void NodeSetEnabled_18bbc0(Obj_FUN_0018bbc0 *o, s32 p1)
{
    o->m32 = (p1 != 0);
}
