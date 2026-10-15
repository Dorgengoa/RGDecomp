#include "types.h"
/* normal 0x00511910 -- `blezl` guard, shared `return 0` in the delay slot. */

typedef struct Obj { u8 pad00[0x14]; u8 f14; } Obj;

extern void func_291910(Obj *p);

s32 normal_SpaceMenuWidgetsDraw_511910(Obj *p)
{
    if (p->f14 > 0) {
        func_291910(p);
    }
    return 0;
}
