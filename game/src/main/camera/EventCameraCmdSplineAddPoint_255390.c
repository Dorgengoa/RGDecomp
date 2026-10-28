/* rgp:protos */
#define RGP_SELF_EventCameraCmdSplineAddPoint_255390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EventCameraCmdSplineAddPoint_255390(u8 *a, u8 *b)
{
    SplinePathPairAddPoint_2570a0(b + 0x1C0, a + 0x10, a + 0x20);
    return 0;
}
