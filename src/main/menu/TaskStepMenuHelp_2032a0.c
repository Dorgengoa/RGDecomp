#include "types.h"

extern void func_522FD0(void);

/* A tail-call thunk out of the main image: one `j func_522FD0`, an empty
   delay slot, no argument fixup.  The callee is not main text and has
   no listing, so its ARITY is unknowable here -- w1_arity refuses the
   shape for exactly that reason.  It does not change the code mwcc
   emits: with nothing in the delay slot the call compiles to `j` plus
   a nop whatever the declared signature is, and the byte comparison
   arbitrates.  The address comes from the callee's own name. */

void TaskStepMenuHelp_2032a0(void)
{
    func_522FD0();
}
