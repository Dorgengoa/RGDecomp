#include "types.h"

extern void SplinePathPairAddPoint_2570a0(void *, void *, void *);

s32 EventCameraCmdSplineAddPoint_255390(u8 *a, u8 *b)
{
    SplinePathPairAddPoint_2570a0(b + 0x1C0, a + 0x10, a + 0x20);
    return 0;
}
