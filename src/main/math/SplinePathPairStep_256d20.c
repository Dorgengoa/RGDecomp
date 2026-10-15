#include "types.h"

extern s32 SplineAdvanceByDistance_257330(void *p);
extern void SplineGetPos_257160(void *p, s32 v);

void SplinePathPairStep_256d20(u8 *arg0, s32 arg1, s32 arg2)
{
    s32 flag1;
    s32 flag2;

    if (*(s32 *)(arg0 + 0x940) != 0) {
        flag1 = 0;
        flag2 = 0;
        if (SplineAdvanceByDistance_257330(arg0 + 0x208) != 0) {
            flag1 = 1;
        }
        if (SplineAdvanceByDistance_257330(arg0 + 0x5A4) != 0) {
            flag2 = 1;
        }
        if ((flag1 != 0) && (flag2 != 0)) {
            *(s32 *)(arg0 + 0x940) = 0;
        }
        SplineGetPos_257160(arg0 + 0x208, arg1);
        SplineGetPos_257160(arg0 + 0x5A4, arg2);
    }
}
