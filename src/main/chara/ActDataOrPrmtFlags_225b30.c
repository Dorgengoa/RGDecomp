#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00225b30 {
    u8 pad000[0x8];
    s64 m08;         /* +0x8 */
} Obj_FUN_00225b30;

void ActDataOrPrmtFlags_225b30(Obj_FUN_00225b30 *o, s64 p1)
{
    o->m08 = (o->m08 | p1);
}
