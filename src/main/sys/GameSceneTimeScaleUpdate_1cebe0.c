#include "types.h"

typedef struct {
    u8 pad[0x5E04];
    s32 u5E04;
    f32 u5E08;
    f32 u5E0C;
    s32 u5E10;
} T1cebe0;

f32 DrawCtxGetFrameTime_144120(s32);
s32 GetDrawCtx_15de80();
s32 GameSceneTimeScaleIsSuspendedMaybe_1cebb0(T1cebe0 *);
s32 GameSceneTimeScaleIsLockedMaybe_1cebc0(T1cebe0 *);
s32 GameSceneIsDoubleStepModeMaybe_1cebd0(T1cebe0 *);
extern f32 D_0047D464;

void GameSceneTimeScaleUpdate_1cebe0(T1cebe0 *arg0) {
    f32 f;
    s32 t;
    s32 c;

    t = arg0->u5E10;
    if (t > 0) {
        t = t - 1;
        arg0->u5E10 = t;
        if (t == 0) {
            arg0->u5E08 = 1.0f;
            arg0->u5E10 = -1;
        }
    }
    arg0->u5E0C = 1.0f;
    arg0->u5E04 = 1;
    if (GameSceneTimeScaleIsLockedMaybe_1cebc0(arg0) == 0) {
        switch (GameSceneTimeScaleIsSuspendedMaybe_1cebb0(arg0)) {
        case 0:
            break;
        default:
            return;
        }
        f = DrawCtxGetFrameTime_144120(GetDrawCtx_15de80()) / 2.0f;
        if (!(f <= 1.0f)) {
            if (GameSceneIsDoubleStepModeMaybe_1cebd0(arg0) != 0) {
                if (!(f <= D_0047D464)) {
                    arg0->u5E04 = 2;
                    return;
                }
                return;
            } else {
                if (!(arg0->u5E0C <= 2.0f)) {
                    arg0->u5E0C = 2.0f;
                }
                arg0->u5E0C = f;
            }
        }
    }
}
