/* rgp:protos */
#define RGP_SELF_AtkPrmGetKnockbackDirMode_3f8c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003f8c90 {
    u8 pad000[0x10];
    s32 m10;         /* +0x10 */
} Obj_FUN_003f8c90;

s32 AtkPrmGetKnockbackDirMode_3f8c90(Obj_FUN_003f8c90 *o)
{
    return (o->m10 & 0xF0);
}
