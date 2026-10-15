#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00311590 {
    u8 pad000[0xE];
    s16 m0E;         /* +0xE */
    s16 m10;         /* +0x10 */
} Obj_FUN_00311590;

void NavEdgeSetBothDirFlags_311590(Obj_FUN_00311590 *o)
{
    o->m0E = 1;
    o->m10 = 1;
}
