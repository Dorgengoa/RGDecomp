#include "types.h"

extern f32 GameSceneGetTimeStep_1ceba0(s32 arg0);
extern s32 GetCurrentScene_1f5be0(void);
extern f32 D_00481B94;
extern f32 D_00481B98;

void IconStealthStep_202950(void) {
    f32 result;
    f32 t;
    f32 old94;
    f32 old98;

    result = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    old94 = D_00481B94;
    old98 = D_00481B98;
    t = old94 + old98 * result;
    D_00481B94 = t;
    if (t < 0.0f) {
        D_00481B94 = 0.0f;
        D_00481B98 = 0.0f;
    }

    if (!(D_00481B94 <= 1.0f)) {
        D_00481B94 = 1.0f;
        D_00481B98 = 0.0f;
    }
}
