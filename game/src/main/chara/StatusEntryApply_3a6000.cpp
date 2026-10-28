#include "types.h"

struct S {
    u8 x0;
    s8 x1;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 pad3;
    f32 x4;
};

extern "C" s32 StatusEntryIsRunning_3a6190(S *);
extern "C" u8 *GetGameData_1fede0(void);
extern "C" f32 D_0045B078[];

extern "C" s32 StatusEntryApply_3a6000(S *arg0, u8 arg1, s8 arg2, s32 arg3)
{
    f32 t;
    s32 f;

    if (arg3 == 0) {
        if (arg0->x0 != 0 || StatusEntryIsRunning_3a6190(arg0) != 0) {
            return 0;
        }
    }
    { f32 v = *(f32 *)(*(u8 **)(*(u8 **)(*(u8 **)(GetGameData_1fede0() + 8) + 0x54) + 8) + 0xC0); t = v * D_0045B078[0]; }
    arg0->x0 = arg1;
    arg0->x1 = arg2;
    f = 0;
    arg0->b0 = true;
    arg0->b1 = f;
    arg0->b2 = f;
    arg0->x4 = 2.0f * t;
    return 1;
}
