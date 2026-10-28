/* rgp:protos */
#define RGP_SELF_MovingLineInit_2d5f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MovingLineInit_2d5f40(void *p)
{
    u8 *q;

    q = (u8 *)p;
    *(s16 *)(q + 0x120) = 0;
    *(s32 *)(q + 0x140) = 0;
    TrailRibbonReset_32c880(q + 0x100);
    TrailRibbonSetEnabled_32c820(q + 0x100, 1);
    TrailRibbonSetVertexColor_32c7d0(q + 0x100, 0);
    TrailRibbonSetTextured_32c780(q + 0x100, 1);
}
