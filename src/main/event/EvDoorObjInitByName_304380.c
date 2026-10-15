#include "types.h"

extern void EvDoorObjReset_304440(void);
extern void TargetRefSetMapNode_2e6370(void *a, s32 b, s32 c, f32 d);
extern void EvObjInitByName_2f9de0(void *a, s32 b, s32 c, s32 d);

void EvDoorObjInitByName_304380(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s16 arg7, s32 arg_sp0, s32 arg_sp8)
{
    EvDoorObjReset_304440();
    EvObjInitByName_2f9de0(arg0, arg1, arg2, arg3);
    TargetRefSetMapNode_2e6370(arg0 + 0xA0, arg4, arg5, 0.0f);
    *(s32 *) (arg0 + 0x184) = arg6;
    *(s16 *) (arg0 + 0x18A) = arg7;
    *(s32 *) (arg0 + 0x180) = arg_sp0;
    *(s16 *) (arg0 + 0x188) = (s16) arg_sp8;
}
