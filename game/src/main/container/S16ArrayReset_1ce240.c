/* rgp:protos */
#define RGP_SELF_S16ArrayReset_1ce240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001ce240 {
    s32 m00;         /* +0x0 */
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
} Obj_FUN_001ce240;

void S16ArrayReset_1ce240(Obj_FUN_001ce240 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m06 = 0;
}
