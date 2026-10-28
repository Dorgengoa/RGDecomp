/* rgp:protos */
#define RGP_SELF_CameraQueueEyeYaw_161220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00161220 {
    u8 pad000[0x218];
    s32 m218;         /* +0x218 */
    f32 m21C;         /* +0x21C */
} Obj_FUN_00161220;

void CameraQueueEyeYaw_161220(Obj_FUN_00161220 *o, f32 fa0)
{
    o->m218 = 1;
    o->m21C = fa0;
}
