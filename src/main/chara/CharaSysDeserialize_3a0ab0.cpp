#include "types.h"

/* jalr through vtable slot 0x1C: virtual_index = (0x1C - 8) / 4 = 5.
 * [[jalr-is-cpp-virtual]] */

class VE {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4();
    virtual s32  v5();          /* slot 0x1C */
};

extern "C" const s32 D_004658F8;
extern "C" void CharaSysEncounterResetMaybe_3a5b10(VE *arg0, s32 arg1, s32 arg2, s32 arg3);

extern "C" s32 CharaSysDeserialize_3a0ab0(VE *arg0, s32 arg1, s32 arg2)
{
    s32 temp_16;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    temp_16 = 0;
    if (D_004658F8 < arg2) {
        return 0;
    }
    temp_16 += arg0->v5();
    CharaSysEncounterResetMaybe_3a5b10(arg0, 1, 1, 1);
    return temp_16;
}
