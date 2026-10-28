/* rgp:protos */
#define RGP_SELF_EvScriptCmdVolumeAdd_3012e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern u8 D_00451E40[0x400];
extern u8 D_00451E60[0x400];
extern V4 D_0047F0E0 __attribute__((section(".sdata")));
extern V4 D_0047F0F0 __attribute__((section(".sdata")));
extern s32 D_00482830;
extern s32 D_00482834;

s32 EvScriptCmdVolumeAdd_3012e0(s32 arg0, s32 arg1) {
    V4 a __attribute__((aligned(16)));
    s32 base;
    s32 h;

    if (arg1 != 5 && arg1 != 8 && arg1 != 0xB) {
        return 0;
    }
    if (D_00482830 == 0 || D_00482834 >= 0x40) return 1;
    a = D_0047F0E0;
    {
        V4 b __attribute__((aligned(16))) = {0};
        V4 c __attribute__((aligned(16)));
        *(V4 *)&c = D_0047F0F0;
        base = D_00482830 + (D_00482834 << 6);
        if (arg1 >= 5) {
            a.x = ScriptArgGetFloat_301a20(arg0 + 0x10);
            a.y = ScriptArgGetFloat_301a20(arg0 + 0x18);
            a.z = ScriptArgGetFloat_301a20(arg0 + 0x20);
        }
        if (arg1 >= 8) {
            b.x = ScriptArgGetFloat_301a20(arg0 + 0x28);
            b.y = ScriptArgGetFloat_301a20(arg0 + 0x30);
            b.z = ScriptArgGetFloat_301a20(arg0 + 0x38);
        }
        if (arg1 >= 0xB) {
            c.x = ScriptArgGetFloat_301a20(arg0 + 0x40);
            c.y = ScriptArgGetFloat_301a20(arg0 + 0x48);
            c.z = ScriptArgGetFloat_301a20(arg0 + 0x50);
        }
        h = ParseFlagNames_1ca700(ScriptArgGetStr_301a00(arg0), D_00451E40, 0);
        EventVolumeInit_2e54f0(base, h, ParseFlagNames_1ca700(ScriptArgGetStr_301a00(arg0 + 8), D_00451E60, 0), &a, &b, &c);
    }
    D_00482834 += 1;
    return 1;
}
