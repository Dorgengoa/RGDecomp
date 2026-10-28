/* rgp:protos */
#define RGP_SELF_insect_MotionEventSeEndThunk_5109d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005109D0 -- pass-28 unnamed-listing conversion.  EXTERNAL TAIL-CALL
 * THUNK: one `j func_1B1240`, EMPTY delay slot, padding nops.  With nothing in
 * the slot there is no argument fixup to reproduce, so the callee's real
 * arity is NOT recovered here and the `void` signature below is the class,
 * not a reading of the callee -- see memory/subsystem-decomp-track \"the
 * external tail-call thunk\". */
/*rgp*/

void insect_MotionEventSeEndThunk_5109d0(int rgp_a0, void *rgp_a1)
{
    MotionEventSeEnd_1b1240((int)rgp_a0, (void *)rgp_a1);
}
