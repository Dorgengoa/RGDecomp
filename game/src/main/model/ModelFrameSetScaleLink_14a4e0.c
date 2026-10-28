/* rgp:protos */
#define RGP_SELF_ModelFrameSetScaleLink_14a4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0014a4e0 {
    u8 pad000[0x1C];
    s32 m1C;         /* +0x1C */
    u8 pad020[0x9];
    u8 m29;         /* +0x29 */
    u8 pad02A[0x1];
    u8 m2B;         /* +0x2B */
} Obj_FUN_0014a4e0;

void ModelFrameSetScaleLink_14a4e0(Obj_FUN_0014a4e0 *o, s32 p1)
{
    o->m1C = p1;
    o->m2B = 1;
    o->m29 = 1;
}
