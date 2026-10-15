#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 Bit64Test_33de60(s32, s32);

s32 UiPanelIsOpen_33dd30(s32 a4)
{
    return Bit64Test_33de60(a4, 0);
}
