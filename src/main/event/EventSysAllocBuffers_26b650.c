#include "types.h"

extern s32 ConstructNewArray_100710(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 MemStackNew_14e1b0(s32 arg0, s32 arg1);
extern s32 MemStackNew_14e230(s32 arg0, s32 arg1);
extern s32 EventCameraCtor_254c50(s32 arg0);
extern void EventSysInit_26b460(void);
extern void EventStateInitMaybe_26b740(void);
extern s32 D_00482054;
extern s32 D_00482058;
extern s32 D_0048205C;
extern s32 D_00482060;
extern s32 D_00482064;
extern s32 D_00482068;
extern s32 D_0048206C;
extern void MenuWinCtor_26c510();
extern void EvSubMachineSplineCtor_252090();

void EventSysAllocBuffers_26b650(s32 arg0)
{
    s32 var_2;

    D_00482054 = MemStackNew_14e1b0(0x8010, arg0);
    D_00482058 = MemStackNew_14e1b0(0x1410, arg0);
    D_0048205C = MemStackNew_14e1b0(0xC00, arg0);
    var_2 = MemStackNew_14e230(0xB10, arg0);
    if (var_2 != 0) {
        var_2 = EventCameraCtor_254c50(var_2);
    }
    D_00482060 = var_2;
    D_00482064 = MemStackNew_14e1b0(0x2800, arg0);
    D_00482068 = ConstructNewArray_100710(MemStackNew_14e1b0(0xBE10, arg0), (void *)EvSubMachineSplineCtor_252090, 0, 0x5F0, 0x20);
    D_0048206C = ConstructNewArray_100710(MemStackNew_14e1b0(0x710, arg0), (void *)MenuWinCtor_26c510, 0, 0xE0, 8);
    EventStateInitMaybe_26b740();
    EventSysInit_26b460();
}
