#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 EventScriptRunTwoPass_2fd9d0(s32, s32, s32, s32);

s32 EventScriptRunTwoPassFwd_2fd960(s32 a4, s32 a5, s32 a6, s32 a7, s32 a8)
{
    return EventScriptRunTwoPass_2fd9d0(a4, a5, a8, a7);
}
