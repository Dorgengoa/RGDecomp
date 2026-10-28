/* rgp:protos */
#define RGP_SELF_EvObjLiftStallFrame_335a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T335A00 { u8 pad000[0x10A]; s16 f10A; };

void EvObjLiftStallFrame_335a00(struct T335A00 *p)
{
    p->f10A--;
    if (p->f10A < 0) {
        p->f10A = 0;
    }
}
