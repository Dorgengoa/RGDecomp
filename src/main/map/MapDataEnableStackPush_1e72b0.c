#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001e72b0 {
    u8 pad000[0x23];
    u8 m23;         /* +0x23 */
} Obj_FUN_001e72b0;

void MapDataEnableStackPush_1e72b0(Obj_FUN_001e72b0 *o)
{
    o->m23 = (o->m23 << 1);
}
