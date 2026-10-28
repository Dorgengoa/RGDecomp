/* rgp:protos */
#define RGP_SELF_AttackChainReleaseHit_382bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00382bf0 {
    u8 pad000[0xE];
    s16 m0E;         /* +0xE */
} Obj_FUN_00382bf0;

s32 AttackChainReleaseHit_382bf0(Obj_FUN_00382bf0 *o)
{
    o->m0E = (o->m0E + 1);
    return 1;
}
