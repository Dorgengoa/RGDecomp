#include "types.h"

struct T335A00 { u8 pad000[0x10A]; s16 f10A; };

void EvObjLiftStallFrame_335a00(struct T335A00 *p)
{
    p->f10A--;
    if (p->f10A < 0) {
        p->f10A = 0;
    }
}
