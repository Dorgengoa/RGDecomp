#include "types.h"

extern void MenuEasyStackInit_206360(s32);
extern void LeaderSwitchMenuInit_39d210(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EasyMenuOpen_2030d0(void)
{
    MenuEasyStackInit_206360(0x10);
    LeaderSwitchMenuInit_39d210();
}
