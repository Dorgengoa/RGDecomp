#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s64 D_00483160;

typedef struct Obj_FUN_00373050 {
    s64 m00;         /* +0x0 */
} Obj_FUN_00373050;

void McSaveGetMergedFlags_373050(Obj_FUN_00373050 *o)
{
    o->m00 = D_00483160;
}
