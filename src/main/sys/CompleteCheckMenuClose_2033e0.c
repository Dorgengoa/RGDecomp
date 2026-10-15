#include "types.h"

extern void CompleteCheckResRelease_203410(void);
extern void MenuTransdataRelease_206260(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CompleteCheckMenuClose_2033e0(void)
{
    CompleteCheckResRelease_203410();
    MenuTransdataRelease_206260();
}
