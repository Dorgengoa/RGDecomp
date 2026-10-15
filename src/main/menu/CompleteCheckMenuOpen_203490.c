#include "types.h"

extern void MenuTransdataInit_206270(void);
extern void CompleteCheckInit_39eac0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CompleteCheckMenuOpen_203490(void)
{
    MenuTransdataInit_206270();
    CompleteCheckInit_39eac0();
}
