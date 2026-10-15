#include "types.h"

extern void MenuReadBufInit_206460(s32);
extern void MainMenuInit_297510(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MainMenuOpen_204a20(void)
{
    MenuReadBufInit_206460(0x120C8);
    MainMenuInit_297510();
}
