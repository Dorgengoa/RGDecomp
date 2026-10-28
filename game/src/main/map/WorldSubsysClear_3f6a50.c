/* rgp:protos */
#define RGP_SELF_WorldSubsysClear_3f6a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003f6a50 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    u8 pad008[0x4];
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
    s32 m14;         /* +0x14 */
    s32 m18;         /* +0x18 */
} Obj_FUN_003f6a50;

void WorldSubsysClear_3f6a50(Obj_FUN_003f6a50 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m0C = 0;
    o->m10 = 0;
    o->m14 = 0;
    o->m18 = 0;
}
