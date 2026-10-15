#include "types.h"

typedef struct Obj00309300 {
    u8 pad0[0x26C];
    s8 unk26C;
} Obj00309300;

void GetCurrentScene_1f5be0(void);
s32 CameraModeGetCurrent_309370(Obj00309300 *arg0);
void CameraModeSetTop_309440(Obj00309300 *arg0, s32 val);
void CameraApplyMode_309490(Obj00309300 *arg0, s64 val);

void CameraSetModeOverride_309300(Obj00309300 *arg0, s64 arg1)
{
    GetCurrentScene_1f5be0();
    arg0->unk26C = (s8)arg1;
    if ((s8)arg1 == -1) {
        CameraModeSetTop_309440(arg0, CameraModeGetCurrent_309370(arg0));
    } else {
        CameraApplyMode_309490(arg0, arg1);
    }
}
