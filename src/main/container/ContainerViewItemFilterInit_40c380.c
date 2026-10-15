#include "types.h"

typedef struct {
    u8 pad0[4];
    s32 m4;
    s16 m8;
    s16 mA;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 pad : 4;
    u8 padD;
    s16 mE;
    s16 m10;
} S40C;

void ContainerViewItemFilterInit_40c380(S40C *arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg0->m4 = arg1;
    arg0->m8 = arg2;
    arg0->mA = arg3;
    arg0->b0 = arg4;
    arg0->b1 = arg5;
    arg0->b3 = arg6;
    arg0->b2 = arg7;
    arg0->mE = -1;
    arg0->m10 = -1;
}
