#include "types.h"

typedef struct { f32 x, y, z, w; } V4_385700;
extern void ModelSetPos_151110(s32 arg0, void *arg1);
extern void MotionListResetAll_171e00(s32 arg0);
extern V4_385700 D_0047FBC0 __attribute__((section(".sdata")));

void MenuObjSetHideModels_385700(s32 arg0)
{
    V4_385700 v;
    s32 p;
    s32 i;

    for (i = 0; i < 2; i++) {
        *(V4_385700 *)&v = D_0047FBC0;
        v.y = -100.0f;
        v.z = -0.0f;
        v.x = 0.0f;
        p = arg0 + i * 0x790;
        ModelSetPos_151110(p + 0x22F0, &v);
        MotionListResetAll_171e00(p + 0x24E0);
    }
}
