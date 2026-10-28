/* rgp:protos */
#define RGP_SELF_HatenaMarkLatchState_345290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00345290 {
    u8 pad000[0xC];
    s8 m0C;         /* +0xC */
    u8 m0D;         /* +0xD */
    u8 pad00E[0x94];
    s16 mA2;         /* +0xA2 */
} Obj_FUN_00345290;

void HatenaMarkLatchState_345290(Obj_FUN_00345290 *o)
{
    o->m0D = o->m0C;
    o->mA2 = -1;
}
