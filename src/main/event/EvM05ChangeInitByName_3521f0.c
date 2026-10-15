#include "types.h"

extern void EvM05ChangeReset_3522b0(void);
extern void TargetRefSetMapObj_2e6470(void *a, s32 b, s32 c, f32 d);
extern void EvObjInitByName_2f9de0(void *a, s32 b, s32 c, s32 d);

void EvM05ChangeInitByName_3521f0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, s32 arg_sp8)
{
    EvM05ChangeReset_3522b0();
    EvObjInitByName_2f9de0(arg0, arg1, arg2, arg3);
    TargetRefSetMapObj_2e6470(arg0 + 0xA0, arg4, arg5, 0.0f);
    *(s32 *) (arg0 + 0x140) = arg6;
    *(s32 *) (arg0 + 0x144) = arg7;
    *(s32 *) (arg0 + 0xE8) = arg_sp0;
    *(s32 *) (arg0 + 0xEC) = arg_sp8;
}
