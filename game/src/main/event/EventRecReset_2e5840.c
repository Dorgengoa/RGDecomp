/* rgp:protos */
#define RGP_SELF_EventRecReset_2e5840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002e5840 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
} Obj_FUN_002e5840;

void EventRecReset_2e5840(Obj_FUN_002e5840 *o)
{
    o->m00 = 0;
    o->m08 = -1;
    o->m04 = -1;
    o->m0C = 0;
}
