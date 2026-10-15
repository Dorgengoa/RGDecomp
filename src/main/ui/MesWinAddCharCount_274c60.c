#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00274c60 {
    u8 pad000[0x1928];
    s32 m1928;         /* +0x1928 */
} Obj_FUN_00274c60;

void MesWinAddCharCount_274c60(Obj_FUN_00274c60 *o, s32 p1)
{
    o->m1928 = (o->m1928 + p1);
}
