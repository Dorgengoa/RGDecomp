/* rgp:protos */
#define RGP_SELF_GameSceneTimeScaleUpdate_1cebe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[0x5E04];
    s32 u5E04;
    f32 u5E08;
    f32 u5E0C;
    s32 u5E10;
} T1cebe0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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
    if (((unsigned char)GameSceneTimeScaleIsLockedMaybe_1cebc0(arg0)) == 0) {
        switch (((unsigned char)GameSceneTimeScaleIsSuspendedMaybe_1cebb0(arg0))) {
        case 0:
            break;
        default:
            return;
        }
        f = DrawCtxGetFrameTime_144120(GetDrawCtx_15de80()) / 2.0f;
        if (!(f <= 1.0f)) {
            if (((unsigned char)GameSceneIsDoubleStepModeMaybe_1cebd0(arg0)) != 0) {
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
