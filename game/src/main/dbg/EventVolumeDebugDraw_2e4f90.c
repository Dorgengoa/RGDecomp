/* rgp:protos */
#define RGP_SELF_EventVolumeDebugDraw_2e4f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

s32 EventVolumeDebugDraw_2e4f90(s32 p0, s32 p1, s32 p2, s32 p3)
{
    u128 v50[4];
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv5;
    s32 r3;
    s32 r4;
    s32 r6;

    r0 = (EventVolumeGetMatrix_2e5630(p0, v50), (s32)0);
    r1 = (MatMul_1cb700(v50, p2, v50), (s32)0);
    r2 = EventVolumeGetShape_2e56f0(p0);
    if (r2 != 3) {
        if (r2 != 2) {
            if (r2 != 1) {
                return r2;
            }
            r3 = (DrawWireSphere_1cc830(p1, v50, p3), (s32)0);
            rv5 = r3;
        } else {
            r4 = (DrawWireCylinder_1cc600(p1, v50, p3), (s32)0);
            rv5 = r4;
        }
    } else {
        r6 = (DrawWireCube_1cc1b0(p1, v50, p3), (s32)0);
        rv5 = r6;
    }
    return rv5;
}
