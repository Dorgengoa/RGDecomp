/* rgp:protos */
#define RGP_SELF_LoadHandleInit_28b610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0028b610 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    u8 m08;         /* +0x8 */
} Obj_FUN_0028b610;

void LoadHandleInit_28b610(Obj_FUN_0028b610 *o)
{
    o->m00 = -1;
    o->m04 = -1;
    o->m08 = 0;
}
