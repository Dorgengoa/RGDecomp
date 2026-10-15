#include "types.h"

extern void RecStackSlotRelease_201d10(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481BF8;
extern u8 D_004BBF80[];

void MenuTransdataRelease_206260(void)
{
    RecStackSlotRelease_201d10(D_004BBF80, &D_00481BF8);
}
