/* rgp:protos */
#define RGP_SELF_UiPageClearMemStack_289c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00289c50 {
    u8 pad000[0x34];
    s32 m34;         /* +0x34 */
} Obj_FUN_00289c50;

s32 UiPageClearMemStack_289c50(Obj_FUN_00289c50 *o)
{
    o->m34 = 0;
    return 0;
}
