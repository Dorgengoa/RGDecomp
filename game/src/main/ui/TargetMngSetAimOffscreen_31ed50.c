/* rgp:protos */
#define RGP_SELF_TargetMngSetAimOffscreen_31ed50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0031ed50 {
    u8 pad000[0x140];
    s32 m140;         /* +0x140 */
} Obj_FUN_0031ed50;

void TargetMngSetAimOffscreen_31ed50(Obj_FUN_0031ed50 *o)
{
    o->m140 = 2;
}
