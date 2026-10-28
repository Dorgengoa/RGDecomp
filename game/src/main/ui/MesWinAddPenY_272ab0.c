/* rgp:protos */
#define RGP_SELF_MesWinAddPenY_272ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00272ab0 {
    u8 pad000[0x1938];
    s32 m1938;         /* +0x1938 */
} Obj_FUN_00272ab0;

void MesWinAddPenY_272ab0(Obj_FUN_00272ab0 *o, s32 p1)
{
    o->m1938 = (o->m1938 + p1);
}
