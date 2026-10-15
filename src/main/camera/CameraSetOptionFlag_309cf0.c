#include "types.h"

typedef struct {
    u8 pad0[0x274];
    s32 unk274;
} Obj00309CF0;

extern Obj00309CF0 *ObjRecGetLiveObject_1c3bc0(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void CameraResetParams_3090a0(Obj00309CF0 *, s32);
extern s64 CameraModeGetCurrent_309370(Obj00309CF0 *);

void CameraSetOptionFlag_309cf0(s32 arg0) {
    s32 temp_2;
    Obj00309CF0 *obj;

    temp_2 = GetCurrentScene_1f5be0();
    obj = ObjRecGetLiveObject_1c3bc0(temp_2, 1);
    if (obj != NULL) {
        obj->unk274 = arg0 & 0xFF;
        if (((s64)(s8)CameraModeGetCurrent_309370(obj)) == 2) {
            CameraResetParams_3090a0(obj, temp_2);
        }
    }
}
