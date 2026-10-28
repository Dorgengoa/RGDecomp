/* rgp:protos */
#define RGP_SELF_CharaTableEntrySetEndLandOrHit_226020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00226020 {
    u8 pad000[0x3A];
    s16 m3A;         /* +0x3A */
} Obj_FUN_00226020;

void CharaTableEntrySetEndLandOrHit_226020(Obj_FUN_00226020 *o)
{
    o->m3A = 4;
}
