#include "types.h"

extern "C" s32 SoundStreamIsOpen_1c0280(s32 *p)
{
    s32 t;
    bool b;

    t = *p < 0;
    b = t;
    return b ^ 1;
}
