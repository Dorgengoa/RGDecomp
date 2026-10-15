#include "types.h"

extern void MinimapSlotInit_322580(void *);

struct Obj0 {
    u8 pad000[0x510];
    s32 m510;
    s32 m514;
    s32 m518;
    s32 m51C;
    u8 m520;
};

void MinimapMgrInit_3222d0(struct Obj0 *p0)
{
    s32 l0;

    l0 = 0;
    do {
        MinimapSlotInit_322580((u8 *)p0 + ((l0 * 27) << 4));
        l0 = (l0 + 1);
    } while (l0 < 3);
    p0->m510 = 0;
    p0->m514 = 0;
    p0->m518 = 0x3F800000;
    p0->m51C = 0;
    p0->m520 = 0;
}
