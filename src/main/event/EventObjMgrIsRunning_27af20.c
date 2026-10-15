#include "types.h"

extern s32 GetGameMode_1f59c0(void);
extern u8 D_00482188;

s32 EventObjMgrIsRunning_27af20(void)
{
    s32 t;

    t = GetGameMode_1f59c0();
    switch (t) {
    case 6:
    case 7:
        return 1;
    }
    return !(D_00482188 != 0);
}
