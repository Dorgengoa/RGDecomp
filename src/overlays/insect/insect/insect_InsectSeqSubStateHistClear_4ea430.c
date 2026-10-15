#include "types.h"
/* insect 0x004EA430 -- 44 bytes, 11 instructions.  The address is
 * `base + i*4` with the store at a constant +0x14, i.e. a s32 array indexed
 * five past the base. */

void insect_InsectSeqSubStateHistClear_4ea430(s32 *a)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        a[i + 5] = -1;
    }
}
