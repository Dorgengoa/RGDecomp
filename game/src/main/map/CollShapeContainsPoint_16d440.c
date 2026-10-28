/* rgp:protos */
#define RGP_SELF_CollShapeContainsPoint_16d440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 CollShapeContainsPoint_16d440(u8 *a, void *b)
{
    return AabbContainsPoint_13e130(b, a + 0x10, a + 0x20) != 0;
}
