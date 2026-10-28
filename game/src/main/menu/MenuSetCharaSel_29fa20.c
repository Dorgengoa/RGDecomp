/* rgp:protos */
#define RGP_SELF_MenuSetCharaSel_29fa20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0029fa20 {
    u8 pad000[0x68];
    s32 m68;         /* +0x68 */
} Obj_FUN_0029fa20;

s32 MenuSetCharaSel_29fa20(Obj_FUN_0029fa20 *o, s32 p1)
{
    o->m68 = p1;
    return 1;
}
