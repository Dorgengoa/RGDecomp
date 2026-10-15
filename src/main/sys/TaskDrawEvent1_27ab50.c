#include "types.h"

extern s32 SysModeMsgIsKeyCapWarpStartMaybe_27bc40(void);
extern void MenuWinUpdateAll_26b390(void);

void TaskDrawEvent1_27ab50(void)
{
    if (SysModeMsgIsKeyCapWarpStartMaybe_27bc40() == 0) {
        MenuWinUpdateAll_26b390();
    }
}
