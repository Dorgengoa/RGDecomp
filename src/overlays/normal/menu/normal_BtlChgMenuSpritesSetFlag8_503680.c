#include "types.h"
/* normal 0x00503680 -- sets bit 3 of the u16 at +0x1C across `n` 0x20-byte
 * records.  A NEGATIVE count is clamped to 1 (the `bgezl` with `i = 0` in the
 * delay slot is the taken side).  The walk is a POINTER increment with a
 * separate counter, not `p[i]`. */

typedef struct Rec { u8 pad000[0x1C]; u16 f01C; u8 pad01E[2]; } Rec;

void normal_BtlChgMenuSpritesSetFlag8_503680(Rec *p, s32 n)
{
    s32 i;

    if (p != NULL) {
        if (n < 0) {
            n = 1;
        }
        for (i = 0; i < n; i++) {
            p->f01C |= 8;
            p++;
        }
    }
}
