#include "types.h"
extern void *GetKeyCapModeMaybe_1c3540(void);
extern s16 *SysGetModeMsg_1c39b0(void);

s32 StreamPlayAllowedMaybe_2f5210(void)
{
    s16 v;

    if (GetKeyCapModeMaybe_1c3540() == 0) {
        return 1;
    }
    v = *SysGetModeMsg_1c39b0();
    if (v == 6 || v == 2) {
        return 1;
    }
    return 0;
}
