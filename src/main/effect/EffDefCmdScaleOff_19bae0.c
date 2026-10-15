#include "types.h"

struct S19BAE0 { u8 pad000[0x68]; u8 f68; };
struct T19BAE0 { u8 pad000[0x2C]; struct S19BAE0 *f2C; };

s32 EffDefCmdScaleOff_19bae0(s32 a, s32 b, struct T19BAE0 **pp)
{
    struct S19BAE0 *s;

    s = (*pp)->f2C;
    if (s == 0) {
        return 0;
    }
    s->f68 = 1;
    return 1;
}
