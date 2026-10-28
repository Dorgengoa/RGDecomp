#include "types.h"
struct Obj0 { u8 pad000[0x46C]; s32 m46C; u8 pad470[0x5F0]; s32 mA60; };
extern "C" struct Obj0 *D_00482040;
extern "C" s32 EvtCurCanSkip_26a870(void)
{
    bool b;
    if (D_00482040 == 0) {
        return 0;
    }
    if (D_00482040->m46C == 0) {
        return 0;
    }
    b = (D_00482040->mA60 & 1) != 0;
    return !b;
}
