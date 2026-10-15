#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00289c40 {
    u8 pad000[0x34];
    s32 m34;         /* +0x34 */
} Obj_FUN_00289c40;

s32 UiPageSetMemStack_289c40(Obj_FUN_00289c40 *o, s32 p1)
{
    o->m34 = p1;
    return 1;
}
