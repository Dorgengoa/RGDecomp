/* rgp:protos */
#define RGP_SELF_DebugItemIconGridInit_29a2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0029a2d0 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
    s32 m08;         /* +0x8 */
    u8 pad00C[0x4];
    s32 m10;         /* +0x10 */
} Obj_FUN_0029a2d0;

void DebugItemIconGridInit_29a2d0(Obj_FUN_0029a2d0 *o)
{
    o->m02 = 0;
    o->m00 = 0;
    o->m06 = 0;
    o->m04 = 0;
    o->m10 = 0;
    o->m08 = 0;
}
