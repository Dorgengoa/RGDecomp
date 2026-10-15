#include "types.h"

extern void EventRecInitWithKey_2e5800(void *, s32);
extern void TargetRefSetMapObj_2e6470(void *, s32, s32, f32);
extern void EvObjInitByName_2f9de0(void *, s32, s32, s32);
extern void EvNodeAttachObjReset_3535c0(void);

void EvNodeAttachObjInitByName_3534e0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg_sp0, s32 arg_sp8, s32 arg_sp10, s32 arg_sp18)
{
    EvNodeAttachObjReset_3535c0();
    EvObjInitByName_2f9de0(arg0, arg1, arg2, arg3);
    TargetRefSetMapObj_2e6470((u8 *)arg0 + 0xA0, arg4, arg5, 0.0f);
    EventRecInitWithKey_2e5800((u8 *)arg0 + 0xE0, arg6);
    *(s32 *)((u8 *)arg0 + 0xF0) = 0;
    TargetRefSetMapObj_2e6470((u8 *)arg0 + 0xF4, arg7, arg_sp0, 0.0f);
    *(s32 *)((u8 *)arg0 + 0x12C) = arg_sp8;
    *(s32 *)((u8 *)arg0 + 0x130) = arg_sp10;
    *(s32 *)((u8 *)arg0 + 0x134) = arg_sp18;
}
