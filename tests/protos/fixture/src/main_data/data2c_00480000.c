#include "types.h"
extern void VStepA_401000(void);
extern void VKind_401080(void);
extern void VDraw_4010c0(void);
u32 D_00480000[5] = {
    0x00000000u, 0x00000000u, (u32)&VStepA_401000, (u32)&VKind_401080, (u32)&VDraw_4010c0
};
