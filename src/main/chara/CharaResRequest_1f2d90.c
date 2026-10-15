#include "types.h"

typedef struct T2 {
    u8  pad0[2];
    s16 f2;
} T2;

typedef struct Obj {
    u8  padD00[0xD00];
    s32 fD00;
} Obj;

extern T2 *CharaResFindById_1efba0(Obj *, s32);
extern s32 CharaResFindFreeSlot_1f0440(Obj *);
extern s32 CharaResRecSetup_1f4800(s32, s32, s32, s32, s32, s32);

s32 CharaResRequest_1f2d90(Obj *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    s32 temp_2_2;
    s32 var_22;
    T2 *temp_2;
    s32 result;

    var_22 = 0;
    temp_2 = CharaResFindById_1efba0(arg0, arg2);
    if (temp_2 != 0) {
        result = arg3 == temp_2->f2;
    } else {
        temp_2_2 = CharaResFindFreeSlot_1f0440(arg0);
        if (temp_2_2 == 0) {
            return 0;
        }
        if (arg5 != 0) {
            var_22 = arg0->fD00;
        }
        result = CharaResRecSetup_1f4800(temp_2_2, arg6, arg2, arg3, arg4, var_22);
    }
    return result;
}
