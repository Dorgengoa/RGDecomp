/* rgp:protos */
#define RGP_SELF_MenuObjSlotModelReset_3848f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
typedef struct {
    f32 x, y, z, w;
} Vec4_003848f0;

extern Vec4_003848f0 D_0047FBC0 __attribute__((section(".sdata")));

void MenuObjSlotModelReset_3848f0(void *arg0) {
    Vec4_003848f0 v __attribute__((aligned(16)));

    MenuObjSlotClear_384990((void *)arg0);
    *(Vec4_003848f0 *)&v = D_0047FBC0;
    v.y = -50.0f;
    v.x = 0.0f;
    v.z = 0.0f;
    ModelSetPos_151110((u8 *)arg0 + 0x10, &v);
    MotionListResetAll_171e00((u8 *)arg0 + 0x200);
}
