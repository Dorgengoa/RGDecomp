/* rgp:protos */
#define RGP_SELF_CameraModePresetToggleUpdate_307e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct X_00307e50 {
    u8 pad0[0x1A];
    s16 f1A;
} X_00307e50;

typedef struct Q_00307e50 {
    u8 pad0[0xC];
    X_00307e50 *fC;
} Q_00307e50;

extern u8 D_004B2570[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CameraModePresetToggleUpdate_307e50(void *a, void *b)
{
    void *r;
    Q_00307e50 *q;
    X_00307e50 *x;
    r = PadIsTriggered_1839f0(D_004B2570, 0x100);
    if (r != 0) {
        q = ((Q_00307e50 *)GetGameData_1fede0());
        x = q->fC;
        if ((x->f1A & 1) == 1) {
            OptionsSetCameraBitMaybe_3d6080(x, 0);
        } else {
            OptionsSetCameraBitMaybe_3d6080(x, 1);
        }
        FieldHudWidget81Open_204050();
        CameraResetParams_3090a0(a);
    }
    return (CameraFollowLeaderStepMaybe_3081e0(a, b, 0, 0, 0, 0), (s32)0);
}
