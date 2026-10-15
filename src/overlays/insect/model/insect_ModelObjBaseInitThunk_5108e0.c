#include "types.h"
/* insect 0x005108E0 -- pass-28 unnamed-listing conversion.  EXTERNAL TAIL-CALL
 * THUNK: one `j func_1867B0`, EMPTY delay slot, padding nops.  With nothing in
 * the slot there is no argument fixup to reproduce, so the callee's real
 * arity is NOT recovered here and the `void` signature below is the class,
 * not a reading of the callee -- see memory/subsystem-decomp-track \"the
 * external tail-call thunk\". */
extern void func_1867B0(void);

void insect_ModelObjBaseInitThunk_5108e0(void)
{
    func_1867B0();
}
