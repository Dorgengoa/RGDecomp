/* rgp:protos */
#define RGP_SELF_FrameSetDirty_14a5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0014a5e0 {
    u8 pad000[0x29];
    u8 m29;         /* +0x29 */
} Obj_FUN_0014a5e0;

void FrameSetDirty_14a5e0(Obj_FUN_0014a5e0 *o)
{
    o->m29 = 1;
}
