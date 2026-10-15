/* PARK 1/3: length-wrong (52w vs retail 54w). */
#include "types.h"
#pragma opt_propagation off

s32 PadGetTriggeredMask_183d00(void *);
void ScriptSetRefInt_249030(s32, s32);
s32 ScriptGetInt_2490f0(void);
extern u8 D_004B2570[0x400];

s32 EvCmdPadCheckButton_242420(s32 arg0) {
    s32 r;
    s32 k;
    s32 f;

    arg0 += 8;
    k = ScriptGetInt_2490f0();
    r = 0;
    f = PadGetTriggeredMask_183d00(D_004B2570);
    switch (k) {
    case 0:
        if (f & 0x20) {
            r = 1;
        }
        break;
    case 1:
        if (f & 0x50) {
            r = 1;
        }
        break;
    case 2:
        if (f & 0x80) {
            r = 1;
        }
        break;
    case 3:
        if (f & 0x100) {
            r = 1;
        }
        break;
    default:
        return 1;
    }
    ScriptSetRefInt_249030(arg0, r);
    return 1;
}
