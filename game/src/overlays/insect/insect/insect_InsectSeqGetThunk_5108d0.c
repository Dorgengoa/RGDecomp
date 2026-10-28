/* rgp:protos */
#define RGP_SELF_insect_InsectSeqGetThunk_5108d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EBDB0 -- 8 bytes.  An INTERNAL tail-call thunk: one
 * `j insect_InsectSeqGet_5108d0` with an EMPTY delay slot, then padding nops.  With
 * nothing in the slot there is no argument fixup, so the `void` signature is
 * the class and not a reading of the callee. */
/*rgp*/

void * insect_InsectSeqGetThunk_5108d0(void)
{
    return insect_InsectSeqGet_5108d0();
}
