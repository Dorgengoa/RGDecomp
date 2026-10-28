#include "types.h"
extern void VStepB_401040(void);
extern void VKind_401080(void);
extern void VDraw_4010c0(void);
u32 D_00480020[5] = {
    0x00000000u, 0x00000000u, (u32)&VStepB_401040, (u32)&VKind_401080, (u32)&VDraw_4010c0
};
