#pragma opt_propagation off
#include "types.h"

extern u32 ParseFlagNames_1ca700(s32 arg0, void *arg1, s32 arg2);
extern void ActTimeAttrInit_227710(u8 *arg0, u64 arg1, f32 arg2, f32 arg3);
extern s32 ScriptArgGetStr_23fba0(s32 arg0);
extern f32 ScriptArgGetFloat_23fbc0(s32 arg0);
extern u8 D_0044C000[0x400];
extern u8 D_0044C1F0[0x400];
extern u8 *D_00481EC8;
extern s32 D_00481ECC;

s32 ActTimeAttr_23b760(s32 arg0, s32 arg1)
{
    u8 *p;
    f32 a;
    f32 b;
    u64 hi;

    if (arg1 != 3) {
        return 0;
    }
    if (D_00481EC8 == 0 || D_00481ECC >= 0x40) {
        return 1;
    }

    p = D_00481EC8 + D_00481ECC * 0x10;
    a = ScriptArgGetFloat_23fbc0(arg0);
    b = ScriptArgGetFloat_23fbc0(arg0 + 8);
    hi = (u64)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 0x10), D_0044C000, 0) << 32;
    ActTimeAttrInit_227710(p, hi | ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 0x10), D_0044C1F0, 0), a, b);

    D_00481ECC += 1;
    return 1;
}
