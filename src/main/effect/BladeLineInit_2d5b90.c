#include "types.h"

extern void TrailRibbonReset_32c880(void *);
extern void TrailRibbonSetEnabled_32c820(void *, s32);
extern void TrailRibbonSetVertexColor_32c7d0(void *, s32);
extern void TrailRibbonSetTextured_32c780(void *, s32);

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
