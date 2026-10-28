/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemErrorMsgCloseFwd_38f170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the worker and report 0x1 unconditionally.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

/*rgp*/

s32 InsectCageMenuItemErrorMsgCloseFwd_38f170(s32 p0, s32 p1)
{
    InsectCageMenuItemErrorMsgClose_38f190(p0, p1);
    return 0x1;
}
