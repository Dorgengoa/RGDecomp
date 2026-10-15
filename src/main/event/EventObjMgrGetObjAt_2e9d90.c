#include "types.h"

extern s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern s32 DListGetAt_42e9f0(s32, s32);

s32 EventObjMgrGetObjAt_2e9d90(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    if (p1 < 0) {
        return 0;
    }
    r0 = EventObjMgrGetTypeList_2e9d60(p0, p2);
    if (r0 == 0) {
        return 0;
    }
    r1 = DListGetAt_42e9f0(r0, p1);
    if (r1 == 0) {
        return 0;
    }
    return r1 + 0x10;
}
