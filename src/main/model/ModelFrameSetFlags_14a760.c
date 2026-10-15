#include "types.h"
/* the `sh` sits in a PLAIN `beqz` slot, so the store happens on both paths and
   the tested value is the SAME (s16) temp that was stored. */
typedef struct P14A760 { u8 pad000[0x26]; s16 m26; u8 pad028[0x5]; u8 m2D; } P14A760;
void ModelFrameSetFlags_14a760(P14A760 *p, s32 v)
{
    s16 t;

    t = (s16)v;
    p->m26 = t;
    if ((t & 0x10) != 0) {
        p->m2D = 1;
    }
}
