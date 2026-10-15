#include "types.h"
/* insect 0x005109B0 -- pass-28 unnamed-listing conversion.  Tail-call thunk
 * that forwards its own two arguments and supplies the third.  Arity read off
 * the callee (main MotionEventSePlay_1b1250 copies $4, $5 and $6 into $20, $19, $18). */
extern s32 func_1B1250(void *a, void *b, s32 c);

s32 insect_MotionEventSeFireThunk_5109b0(void *a, void *b)
{
    return func_1B1250(a, b, 0);
}
