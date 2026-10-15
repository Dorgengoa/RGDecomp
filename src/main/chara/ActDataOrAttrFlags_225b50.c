#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00225b50 {
    s64 m00;         /* +0x0 */
} Obj_FUN_00225b50;

void ActDataOrAttrFlags_225b50(Obj_FUN_00225b50 *o, s64 p1)
{
    o->m00 = (o->m00 | p1);
}
