#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00272ae0 {
    u8 pad000[0x1934];
    s32 m1934;         /* +0x1934 */
} Obj_FUN_00272ae0;

void MesWinAddPenX_272ae0(Obj_FUN_00272ae0 *o, s32 p1)
{
    o->m1934 = (o->m1934 + p1);
}
