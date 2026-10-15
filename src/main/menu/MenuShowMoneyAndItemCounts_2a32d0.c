#include "types.h"



typedef struct {u8 pad[0x18];s32 party;} Ctx;
extern Ctx *GetGameData_1fede0(void);
extern void *UiGetWidgetSubItem_28f2b0(s32 arg0, s32 arg1, s32 arg2);
extern void UiSetWidgetsVisibleById_291110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 InvCountInCategory_3c7ba0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 MenuShowMoneyAndItemCounts_2a32d0(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_4;
    void *temp_2;
    void *temp_2_2;
    Ctx *temp_2_3;

    temp_4 = *arg0;
    if (temp_4 == 0) {
        return 0;
    }
    UiSetWidgetsVisibleById_291110(temp_4, arg1, 1, 1);
    UiSetWidgetsVisibleById_291110(*arg0, arg2, 1, 1);
    temp_2 = UiGetWidgetSubItem_28f2b0(*arg0, arg1, 0);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_2_2 = UiGetWidgetSubItem_28f2b0(*arg0, arg2, 0);
    if (temp_2_2 == NULL) {
        return 0;
    }
    temp_2_3 = GetGameData_1fede0();
    *(s64 *)((u8 *)temp_2 + 0x8) = *(s64 *)((u8 *)(temp_2_3->party) + 0x160);
    *(s64 *)((u8 *)temp_2_2 + 0x8) = (s64)InvCountInCategory_3c7ba0(temp_2_3->party, 0, -1, 0);
    *(s64 *)((u8 *)temp_2_2 + 0x28) = (s64)InvCountInCategory_3c7ba0(temp_2_3->party, 1, -1, 0);
    return 1;
    return 0;
}
