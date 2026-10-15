#include "types.h"

struct T34C780 { u8 pad000[0x76E]; s16 f76E; };

u8 RevelationBoardIsIdle_34c780(struct T34C780 *p)
{
    u8 r;

    r = 0;
    if (p->f76E == 0) {
        r = 1;
    }
    return r;
}
