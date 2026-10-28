/* rgp:protos */
#define RGP_SELF_ScriptCmdNopIntArg_3339f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the worker and report 0x1 unconditionally.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

/*rgp*/

s32 ScriptCmdNopIntArg_3339f0(s32 p0)
{
    ScriptSlotGetInt_3348b0(p0);
    return 0x1;
}
