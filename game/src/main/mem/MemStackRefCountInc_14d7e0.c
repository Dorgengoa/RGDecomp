/* rgp:protos */
#define RGP_SELF_MemStackRefCountInc_14d7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0014d7e0 {
    u8 pad000[0x24];
    s32 m24;         /* +0x24 */
} Obj_FUN_0014d7e0;

void MemStackRefCountInc_14d7e0(Obj_FUN_0014d7e0 *o)
{
    o->m24 = (o->m24 + 1);
}
