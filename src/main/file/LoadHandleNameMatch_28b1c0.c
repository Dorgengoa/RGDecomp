#include "types.h"

extern s32 StrNotEqual_1f5300(void *, void *);

u8 LoadHandleNameMatch_28b1c0(u8 *a, void *b)
{
    s32 r;

    if (b == 0) {
        return 0;
    }
    r = StrNotEqual_1f5300(b, a + 8);
    return (r != 0) ^ 1;
}
