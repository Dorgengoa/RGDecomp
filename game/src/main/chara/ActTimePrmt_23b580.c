/* rgp:protos */
#define RGP_SELF_ActTimePrmt_23b580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044BB40[0x400];
extern u8 D_0044BDA0[0x400];
extern u8 *D_00481ED0;
extern s32 D_00481ED4;

s32 ActTimePrmt_23b580(s32 arg0, s32 arg1)
{
    u8 *p;
    f32 a;
    f32 b;
    f32 c;
    u64 hi;

    if (arg1 != 4) {
        return 0;
    }
    if (D_00481ED0 == 0 || D_00481ED4 >= 0x40) {
        return 1;
    }

    p = D_00481ED0 + D_00481ED4 * 0x14;
    a = ScriptArgGetFloat_23fbc0(arg0);
    b = ScriptArgGetFloat_23fbc0(arg0 + 8);
    c = ScriptArgGetFloat_23fbc0(arg0 + 0x10);
    hi = (u64)((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 0x18), D_0044BB40, 0)) << 32;
    ActTimePrmtInit_227630(p, hi | ((unsigned int)ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 0x18), D_0044BDA0, 0)), a, b, c);

    if (p + 0xC == 0) {
        return 1;
    }
    D_00481ED4 += 1;
    return 1;
}
