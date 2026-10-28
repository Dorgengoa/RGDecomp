/* rgp:protos */
#define RGP_SELF_CameraSetModeOverride_309300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj00309300 {
    u8 pad0[0x26C];
    s8 unk26C;
} Obj00309300;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CameraSetModeOverride_309300(Obj00309300 *arg0, s64 arg1)
{
    GetCurrentScene_1f5be0();
    arg0->unk26C = (s8)arg1;
    if ((s8)arg1 == -1) {
        CameraModeSetTop_309440(arg0, CameraModeGetCurrent_309370(arg0));
    } else {
        CameraApplyMode_309490(arg0, (signed char)(arg1));
    }
}
