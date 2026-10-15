#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

s32 PcIdToWeaponResIndexMaybe_1f4f70(s32 o, s32 p1)
{
    return (p1 + (((o + -0x2AF9) << 1) + 0x289));
}
