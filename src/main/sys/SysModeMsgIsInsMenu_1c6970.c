#include "types.h"

u8 SysModeMsgIsInsMenu_1c6970(s16 *self)
{
    u8 r;
    s16 c;

    r = 0;
    if (self[0] == 2) {
        r = 1;
    } else if (self[0] == 6 && self[2] == 4) {
        c = self[5];
        if (c == 0x1FE) {
            goto one;
        }
        if (c == 0x1FF) {
one:
            r = 1;
        }
    }
    return r;
}
