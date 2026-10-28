/* rgp:protos */
#define RGP_SELF_EventVolumeGetClipMode_2e56e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002e56e0 {
    s32 m00;         /* +0x0 */
} Obj_FUN_002e56e0;

s32 EventVolumeGetClipMode_2e56e0(Obj_FUN_002e56e0 *o)
{
    return (o->m00 & 0xF0);
}
