#include "types.h"

extern void SeventhMysteryResRelease_2034f0(void);
extern void MenuTransdataRelease_206260(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SeventhMysteryMenuClose_2034c0(void)
{
    SeventhMysteryResRelease_2034f0();
    MenuTransdataRelease_206260();
}
