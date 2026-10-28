/* rgp:protos */
#define RGP_SELF_NpcObjSetYaw_2fb900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002fb900 {
    u8 pad000[0xB0];
    s32 mB0;         /* +0xB0 */
    f32 mB4;         /* +0xB4 */
    s32 mB8;         /* +0xB8 */
    s32 mBC;         /* +0xBC */
} Obj_FUN_002fb900;

void NpcObjSetYaw_2fb900(Obj_FUN_002fb900 *o, f32 fa0)
{
    o->mB8 = 0;
    o->mB0 = 0;
    o->mB4 = fa0;
    o->mBC = 0x3F800000;
}
