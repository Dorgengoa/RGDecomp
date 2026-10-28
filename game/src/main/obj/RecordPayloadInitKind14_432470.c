/* rgp:protos */
#define RGP_SELF_RecordPayloadInitKind14_432470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00432470 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
} Obj_FUN_00432470;

void RecordPayloadInitKind14_432470(Obj_FUN_00432470 *o)
{
    o->m00 = 3;
    o->m04 = 0x1E;
}
