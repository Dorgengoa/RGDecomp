/* rgp:protos */
#define RGP_SELF_WorldOnPartyMapAreaChanged_3ec2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003ec2e0 {
    u8 pad000[0x2C];
    u8 m2C;         /* +0x2C */
} Obj_FUN_003ec2e0;

s32 WorldOnPartyMapAreaChanged_3ec2e0(Obj_FUN_003ec2e0 *o)
{
    return (((o->m2C & 1) != 0) ^ 1);
}
