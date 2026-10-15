#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002716c0 {
    u8 pad000[0x1930];
    s32 m1930;         /* +0x1930 */
} Obj_FUN_002716c0;

void MesWinAddScrollTarget_2716c0(Obj_FUN_002716c0 *o, s32 p1)
{
    o->m1930 = (o->m1930 + p1);
}
