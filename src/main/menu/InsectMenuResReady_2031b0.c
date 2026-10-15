#include "types.h"

extern s32 InsectMenuResLoadPollThunk_398420(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 InsectMenuResReady_2031b0(void)
{
    s32 r;

    r = InsectMenuResLoadPollThunk_398420();
    return (r != 0);
}
