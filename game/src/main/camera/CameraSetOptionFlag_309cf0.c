/* rgp:protos */
#define RGP_SELF_CameraSetOptionFlag_309cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x274];
    s32 unk274;
} Obj00309CF0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CameraSetOptionFlag_309cf0(s32 arg0) {
    s32 temp_2;
    Obj00309CF0 *obj;

    temp_2 = GetCurrentScene_1f5be0();
    obj = ((Obj00309CF0 *)ObjRecGetLiveObject_1c3bc0(temp_2, 1));
    if (obj != NULL) {
        obj->unk274 = arg0 & 0xFF;
        if (((s64)(s8)CameraModeGetCurrent_309370(obj)) == 2) {
            CameraResetParams_3090a0(obj);
        }
    }
}
