#include "types.h"

extern void MenuTransdataInit_206270(void);
extern void InsectMenuOpen_397ee0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void InsectMenuOpenWithData_2031d0(s32 p0)
{
    MenuTransdataInit_206270();
    InsectMenuOpen_397ee0(p0);
}
