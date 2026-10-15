#include "types.h"

extern void MenuObjSlotClear_384990(void);
extern void ModelSetPos_151110(void *arg0, void *arg1);
extern void MotionListResetAll_171e00(void *arg0);
typedef struct {
    f32 x, y, z, w;
} Vec4_003848f0;

extern Vec4_003848f0 D_0047FBC0 __attribute__((section(".sdata")));

void MenuObjSlotModelReset_3848f0(void *arg0) {
    Vec4_003848f0 v;

    MenuObjSlotClear_384990();
    *(Vec4_003848f0 *)&v = D_0047FBC0;
    v.y = -50.0f;
    v.x = 0.0f;
    v.z = 0.0f;
    ModelSetPos_151110((u8 *)arg0 + 0x10, &v);
    MotionListResetAll_171e00((u8 *)arg0 + 0x200);
}
