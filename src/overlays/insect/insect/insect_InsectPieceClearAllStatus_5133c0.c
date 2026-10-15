#include "types.h"
/* insect 0x005133C0 -- 40 bytes, 10 instructions.  Clear sixteen bytes. */

void insect_InsectPieceClearAllStatus_5133c0(u8 *p)
{
    s32 i;

    for (i = 0; i < 0x10; i++) {
        p[i] = 0;
    }
}
