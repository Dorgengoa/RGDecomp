#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0039af30 {
    u8 pad000[0xF0];
    s32 mF0;         /* +0xF0 */
} Obj_FUN_0039af30;

void CagePlaceCursorEnd_39af30(Obj_FUN_0039af30 *o)
{
    o->mF0 = -1;
}
