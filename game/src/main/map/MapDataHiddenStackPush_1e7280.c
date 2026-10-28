/* rgp:protos */
#define RGP_SELF_MapDataHiddenStackPush_1e7280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001e7280 {
    u8 pad000[0x24];
    u8 m24;         /* +0x24 */
} Obj_FUN_001e7280;

void MapDataHiddenStackPush_1e7280(Obj_FUN_001e7280 *o)
{
    o->m24 = ((o->m24 << 1) | 1);
}
