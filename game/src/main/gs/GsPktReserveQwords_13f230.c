/* rgp:protos */
#define RGP_SELF_GsPktReserveQwords_13f230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0013f230 {
    u8 pad000[0xF4];
    s32 mF4;         /* +0xF4 */
} Obj_FUN_0013f230;

s32 GsPktReserveQwords_13f230(Obj_FUN_0013f230 *o, s32 p1)
{
    s32 oldF4;

    oldF4 = o->mF4;
    o->mF4 = (o->mF4 + (p1 << 4));
    return oldF4;
}
