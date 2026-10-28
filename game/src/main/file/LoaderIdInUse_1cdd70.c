/* rgp:protos */
#define RGP_SELF_LoaderIdInUse_1cdd70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct S1cdd70 { u8 pad000[0x20]; s32 m20; u8 pad024[0x4]; s32 m28; u8 pad02C[0x4]; s32 m30; };
/*rgp*/

s32 LoaderIdInUse_1cdd70(struct S1cdd70 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    if (p1 < 0) {
        return 0;
    }
    r0 = ((s32)LoaderQueueFindUnitById_1cdc70(p0, p1, &p0->m30, 0));
    if (r0 != 0) {
        return r0;
    }
    r1 = ((s32)LoaderQueueFindUnitById_1cdc70(p0, p1, &p0->m28, 0));
    if (r1 != 0) {
        return r1;
    }
    r2 = ((s32)LoaderQueueFindUnitById_1cdc70(p0, p1, &p0->m20, 0));
    if (r2 != 0) {
        return r2;
    }
    return 0;
}
