/* rgp:protos */
#define RGP_SELF_insect_InsectCursorSetGetEventsExcept_5119b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005119B0 -- 64 bytes, 16 instructions, 1 call.
 *
 * TWO `dsll32/dsra32 ..,0` sign-extensions bracket the `and`: one narrows the
 * callee's 64-bit result to s32, the other widens the s32 `&` back out, so the
 * callee returns s64 and so does this.  $4 is never written -- the first
 * argument is passed straight through.
 *
 * `and $2, $2, $3` puts the CALL RESULT in rs.  Writing the call inline gives
 * `and $2, $3, $2` in every operand order and every complement spelling
 * (4 inert spellings measured: operands swapped, `mask ^ -1`, `~(u32)mask`,
 * and a named local for the COMPLEMENT).  Naming the call RESULT is the whole
 * fix, the same mechanism as insect_FUN_005142D0 in this batch.
 */

typedef struct Ins Ins;

/*rgp*/

s64 insect_InsectCursorSetGetEventsExcept_5119b0(Ins *o, s32 mask)
{
    s32 r;

    r = (s32)insect_InsectCursorSetGetEvents_5119f0(o, -1);
    return r & ~mask;
}
