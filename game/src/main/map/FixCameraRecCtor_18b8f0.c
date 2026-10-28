/* rgp:protos */
#define RGP_SELF_FixCameraRecCtor_18b8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 FixCameraRecCtor_18b8f0(s32 p0)
{
    u8 *q;

    q = (u8 *)p0 + 0xA8;
    do {
        FixCameraOffGroupCtor_18b950((s32)q);
        q = q + 8;
    } while (q < (u8 *)p0 + 0xC8);
    FixCameraRecInit_193860(p0);
    return p0;
}
