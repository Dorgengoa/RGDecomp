/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinReset_243c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { f32 w[4]; } SD4_0047E7F0;
extern SD4_0047E7F0 D_0047E7F0 __attribute__((section(".sdata")));
typedef struct { f32 w[4]; } SD4_0047E800;
extern SD4_0047E800 D_0047E800 __attribute__((section(".sdata")));

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/


s32 EvCmdMenuWinReset_243c70(void *rgp_a0) {
    f32 a[4] __attribute__((aligned(16)));
    f32 b[4] __attribute__((aligned(16)));
    s32 temp_2;

    temp_2 = ((s32)MenuWinGet_2653e0(ScriptGetInt_2490f0((void *)rgp_a0)));
    if (temp_2 == 0) {
        return 0;
    }
    MenuWinInit_26c450(temp_2);
    *(SD4_0047E7F0 *)a = D_0047E7F0;
    *(SD4_0047E800 *)b = D_0047E800;
    MenuWinSetDrawMode_26c3e0(temp_2, 0);
    MenuWinSetBlendMode_26c270(temp_2, 1);
    MenuWinSetPos_26c3b0(temp_2, a);
    MenuWinSetColor_26c380(temp_2, b);
    MenuWinSetSize_26c320(temp_2, 0x200, 0x1C0);
    return 1;
    return 0;
}
