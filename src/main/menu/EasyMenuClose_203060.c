#include "types.h"

extern void LeaderSwitchMenuResetThunk_39d160(void);
extern void Nop_206350(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EasyMenuClose_203060(void)
{
    LeaderSwitchMenuResetThunk_39d160();
    Nop_206350();
}
