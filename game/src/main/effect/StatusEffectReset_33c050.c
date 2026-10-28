/* rgp:protos */
#define RGP_SELF_StatusEffectReset_33c050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0033c050 {
    s32 m00;         /* +0x0 */
    u8 pad004[0x4];
    s32 m08;         /* +0x8 */
} Obj_FUN_0033c050;

void StatusEffectReset_33c050(Obj_FUN_0033c050 *o)
{
    o->m00 = 0;
    o->m08 = 1;
}
