/* rgp:protos */
#define RGP_SELF_MesWinSetClipMode_2721e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002721e0 {
    u8 pad000[0x1C4A];
    s16 m1C4A;         /* +0x1C4A */
} Obj_FUN_002721e0;

void MesWinSetClipMode_2721e0(Obj_FUN_002721e0 *o, s32 p1)
{
    o->m1C4A = (p1 & 0xFF);
}
