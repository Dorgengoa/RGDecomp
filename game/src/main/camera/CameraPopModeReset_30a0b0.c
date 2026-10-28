/* rgp:protos */
#define RGP_SELF_CameraPopModeReset_30a0b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CameraPopModeReset_30a0b0(void)
{
    void *s;
    void *c;

    s = GetCurrentScene_1f5be0();
    c = ObjRecGetLiveObject_1c3bc0(s, *(s32 *)((s32)s + 0x4344));
    if (c == 0) return;
    CameraModePop_309390(c, 1);
    CameraModeUpdate_309770(c);
    CameraTweenFinish_1772b0(c);
}
