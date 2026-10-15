#include "types.h"

extern s32 ShopMenuIsOpenThunk_50ab00(void);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMenuShopIsOpen_25c180(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ShopMenuIsOpenThunk_50ab00();
    r1 = ScriptSetRefInt_26a1e0(p0, (r0 & 0xFF));
    return 1;
}
