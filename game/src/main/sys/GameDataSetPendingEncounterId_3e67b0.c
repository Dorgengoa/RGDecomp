/* rgp:protos */
#define RGP_SELF_GameDataSetPendingEncounterId_3e67b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003e67b0 {
    u8 pad000[0x58];
    s16 m58;         /* +0x58 */
} Obj_FUN_003e67b0;

s32 GameDataSetPendingEncounterId_3e67b0(Obj_FUN_003e67b0 *o, s32 p1)
{
    o->m58 = p1;
    return 1;
}
