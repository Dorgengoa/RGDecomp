#include "types.h"

struct T1D5810 { u8 pad000[0x17900]; u8 f17900; };

extern void ThreadYield_1d2b70(void);

void MoviePlayerWaitTick_1d5810(struct T1D5810 *p)
{
    s32 i;

    if (p->f17900 == 0) return;
    for (i = 0; i < 4; i++) {
        ThreadYield_1d2b70();
    }
}
