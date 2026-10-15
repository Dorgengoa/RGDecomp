#include "types.h"
/* insect 0x004EBDB0 -- 8 bytes.  An INTERNAL tail-call thunk: one
 * `j insect_InsectSeqGet_5108d0` with an EMPTY delay slot, then padding nops.  With
 * nothing in the slot there is no argument fixup, so the `void` signature is
 * the class and not a reading of the callee. */
extern void insect_InsectSeqGet_5108d0(void);

void insect_InsectSeqGetThunk_5108d0(void)
{
    insect_InsectSeqGet_5108d0();
}
