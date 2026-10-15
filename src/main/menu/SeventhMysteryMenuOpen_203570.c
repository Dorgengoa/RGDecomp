#include "types.h"

extern void MenuTransdataInit_206270(void);
extern void SeventhMysteryInit_395490(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SeventhMysteryMenuOpen_203570(void)
{
    MenuTransdataInit_206270();
    SeventhMysteryInit_395490();
}
