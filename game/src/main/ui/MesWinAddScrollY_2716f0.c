/* rgp:protos */
#define RGP_SELF_MesWinAddScrollY_2716f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002716f0 {
    u8 pad000[0x192C];
    s32 m192C;         /* +0x192C */
} Obj_FUN_002716f0;

void MesWinAddScrollY_2716f0(Obj_FUN_002716f0 *o, s32 p1)
{
    o->m192C = (o->m192C + p1);
}
