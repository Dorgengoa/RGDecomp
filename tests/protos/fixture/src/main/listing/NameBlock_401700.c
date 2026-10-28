#include "types.h"
/* stack-block, 2026-10-19 (b): PutPair_401780 writes {lo, hi} through &sp50 into sp50 and
   sp60 (CollFrameTreeCalcBounds_16be80 shape); sp60 is never address-taken, so only its
   name says it is retail's sp+0x60: the block must place it, not pad the slot */
typedef struct { s32 x, y, z, w; } Q4;
extern void PutPair_401780(Q4 *p);

s32 NameBlock_401700(void)
{
    Q4 sp50;
    Q4 sp60;

    PutPair_401780(&sp50);
    return sp60.x;
}
