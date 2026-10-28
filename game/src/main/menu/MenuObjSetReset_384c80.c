/* rgp:protos */
#define RGP_SELF_MenuObjSetReset_384c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V384c80;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern V384c80 D_0047FBC0 __attribute__((section(".sdata")));

void MenuObjSetReset_384c80(u8 *arg0)
{
    V384c80 a __attribute__((aligned(16)));
    V384c80 b __attribute__((aligned(16)));
    V384c80 c __attribute__((aligned(16)));
    s32 i;

    for (i = 0; i < 2; i++) {
        MenuObjSlotClearFull_384960(arg0 + i * 0xC + 0x1390);
        MenuObjSlotModelReset_3848f0(arg0 + i * 0x7A0 + 0x13B0);
    }
    *(s32 *)(arg0 + 0x0) = 0;
    for (i = 0; i < 2; i++) {
        *(V384c80 *)&a = D_0047FBC0;
        a.y = -50.0f;
        a.x = 0.0f;
        a.z = 0.0f;
        ModelSetPos_151110(arg0 + i * 0x790 + 0x22F0, &a);
    }
    MenuObjSlotClear_384990(arg0 + 0x3210);
    MotionListResetAll_171e00(arg0 + 0x3410);
    *(V384c80 *)&b = D_0047FBC0;
    b.y = -50.0f;
    b.x = 0.0f;
    b.z = 0.0f;
    ModelSetPos_151110(arg0 + 0x3220, &b);
    MenuObjSlotClear_384990(arg0 + 0x39B0);
    MotionListResetAll_171e00(arg0 + 0x3BB0);
    *(V384c80 *)&c = D_0047FBC0;
    c.y = -50.0f;
    c.x = 0.0f;
    c.z = 0.0f;
    ModelSetPos_151110(arg0 + 0x39C0, &c);
    BitArray16Clear_384310(arg0 + 0x4155);
    *(f32 *)(arg0 + 0x4150) = 1.0f;
    *(u8 *)(arg0 + 0x4154) = 0;
}
