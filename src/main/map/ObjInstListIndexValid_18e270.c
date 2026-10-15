#include "types.h"

s32 ObjInstListIndexValid_18e270(void *a, s32 n)
{
    if (n < 0 || n >= 0x7) {
        return 0;
    }
    return 1;
}
