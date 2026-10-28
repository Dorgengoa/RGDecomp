/* rgp:protos */
#define RGP_SELF_BladeLineInit_2d5b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void BladeLineInit_2d5b90(void *p)
{
    u8 *q;

    q = (u8 *)p;
    *(s32 *)(q + 0x00) = 0;
    *(s32 *)(q + 0x40) = 0;
    TrailRibbonReset_32c880(q + 0x50);
    TrailRibbonSetEnabled_32c820(q + 0x50, 1);
    TrailRibbonSetVertexColor_32c7d0(q + 0x50, 0);
    TrailRibbonSetTextured_32c780(q + 0x50, 1);
}
