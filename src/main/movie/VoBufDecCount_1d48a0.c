#include "types.h"
/* retail RE-LOADS the counter after the guard; a plain second read is CSE'd
   with the first, so the guard's read is pinned. */
typedef struct P1D48A0 { u8 pad000[0x10]; s32 m10; } P1D48A0;
void VoBufDecCount_1d48a0(P1D48A0 *p)
{
    if (*(volatile s32 *)&p->m10 > 0) {
        p->m10 = p->m10 - 1;
    }
}
