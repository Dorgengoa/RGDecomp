#include "types.h"

typedef struct {
    u8 pad0[0x214];
    s32 unk214;
    u8 pad218[0x244 - 0x218];
    f32 unk244;
    f32 unk248;
    f32 unk24C;
    s32 unk250;
    s32 unk254;
    s32 unk258;
} Obj0Arg0;

typedef struct {
    f32 a;
    f32 b;
    s32 c;
} In;

extern f32 SysParamTableGetFloat_15fe50(s32, s32);
extern s32 SysParamTableGetInt_15fe80(s32, s32);
extern void CameraObjOrbitControlMaybe_161260(Obj0Arg0 *, In *, s32, s32, s32);

void CameraObjApplyInputMaybe_1619e0(Obj0Arg0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    In s;
    f32 f;

    s.b = 0.0f;
    f = 0.0f;
    s.a = 0.0f;
    s.c = 0;
    if (arg1 != 0) {
        if (!(arg0->unk214 & 2)) {
            f = arg0->unk244 * SysParamTableGetFloat_15fe50(arg1, 6);
        }
        if (!(arg0->unk214 & 1) && ((SysParamTableGetInt_15fe80(arg1, 3) == 0) || (SysParamTableGetInt_15fe80(arg1, 2) == 0))) {
            if (SysParamTableGetInt_15fe80(arg1, 3) != 0) {
                f = arg0->unk24C;
            } else if (SysParamTableGetInt_15fe80(arg1, 2) != 0) {
                f = -arg0->unk24C;
            }
        }
        if (arg0->unk250 > 0) {
            arg0->unk250--;
            f = 0.0f;
        }
        s.a = f * (f32)arg0->unk258;
        s.b = (f32)arg0->unk254 * (arg0->unk248 * -SysParamTableGetFloat_15fe50(arg1, 7));
        s.c = SysParamTableGetInt_15fe80(arg1, 4);
    }
    CameraObjOrbitControlMaybe_161260(arg0, &s, arg2, arg3, arg4);
}
