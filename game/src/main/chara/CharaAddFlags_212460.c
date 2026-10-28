/* rgp:protos */
#define RGP_SELF_CharaAddFlags_212460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00212460 {
    u8 pad000[0x568];
    s64 m568;         /* +0x568 */
} Obj_FUN_00212460;

void CharaAddFlags_212460(Obj_FUN_00212460 *o, s64 p1)
{
    o->m568 = (o->m568 | p1);
}
