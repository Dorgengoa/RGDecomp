/* rgp:protos */
#define RGP_SELF_MapDataEnableStackPop_1e72a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001e72a0 {
    u8 pad000[0x23];
    u8 m23;         /* +0x23 */
} Obj_FUN_001e72a0;

void MapDataEnableStackPop_1e72a0(Obj_FUN_001e72a0 *o)
{
    o->m23 = (((u32)o->m23) >> 1);
}
