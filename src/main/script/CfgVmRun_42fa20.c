#include "types.h"

extern void DelayThread_117618(s32);
extern s32 CfgVmStep_42f6e0(void *, s32);

s32 CfgVmRun_42fa20(void *arg0) {
    s32 var_17;
    s32 ok;

    if ((*(s32 *)((u8 *)arg0 + 0) <= 0) || ((*(s32 *)((u8 *)arg0 + 0x408) == 0) || (*(s32 *)((u8 *)arg0 + 0x40C) <= 0))) return 0;
    *(s32 *)((u8 *)arg0 + 0x424) = 0;
    var_17 = 0;
    for (;;) {
        if (((CfgVmStep_42f6e0(arg0, 1) != 0) ^ 1)) {
            break;
        }
        var_17 += 1;
        if (!(var_17 & 0xFF)) {
            DelayThread_117618(0xA);
        }
    }
    return 1;
}
