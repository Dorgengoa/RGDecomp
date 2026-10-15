#include "types.h"

extern void SoundBankRelease_1bb6e0(s32);
extern void FieldViewModeTeardownMaybe_1fd600(void);
extern void InsectDataStackRelease_31a790(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void FieldModeResReleaseMaybe_2f35b0(void)
{
    SoundBankRelease_1bb6e0(5);
    FieldViewModeTeardownMaybe_1fd600();
    InsectDataStackRelease_31a790();
}
