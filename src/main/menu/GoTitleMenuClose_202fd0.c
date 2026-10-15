#include "types.h"

extern void GoTitleMenuResetThunk_39bf30(void);
extern void Nop_206290(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GoTitleMenuClose_202fd0(void)
{
    GoTitleMenuResetThunk_39bf30();
    Nop_206290();
}
