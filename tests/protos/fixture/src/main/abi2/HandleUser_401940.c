#include "types.h"
/* the decomp's short view of HandleGet_401900: the handle (retail: the caller's own
   entry $a1, never written before the jal) is missing */
extern void **HandleGet_401900(void *t);

void *HandleUser_401940(u8 *o, s32 k)
{
    void **r;

    r = HandleGet_401900(o + 8);
    return r ? r[0] : 0;
}
