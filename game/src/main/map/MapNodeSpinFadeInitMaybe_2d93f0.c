/* rgp:protos */
#define RGP_SELF_MapNodeSpinFadeInitMaybe_2d93f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002d93f0 {
    u8 m00;         /* +0x0 */
    u8 pad001[0x3];
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
} Obj_FUN_002d93f0;

void MapNodeSpinFadeInitMaybe_2d93f0(Obj_FUN_002d93f0 *o)
{
    o->m00 = 1;
    o->m04 = 1;
    o->m08 = 0;
    o->m0C = 0;
}
