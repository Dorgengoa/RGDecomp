/* rgp:protos */
#define RGP_SELF_CharaResLoadDispatch_1f4420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CharaResLoadDispatch_1f4420(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *g;
    s32 k;

    g = ((u8 *)GetGameData_1fede0());
    switch (arg0[7]) {
    case 0:
        CharaResBuildPcWithWeapons_1f4050(arg0, arg1);
        break;
    case 1:
        CharaResBuildNpc_1f3db0(arg0, arg1, arg2);
        break;
    case 2:
        k = *(s16 *)(arg0 + 0x64);
        CharaResBuildMon_1f3860(arg0, arg1, arg2);
        if (k != 4 && *(s16 *)(arg0 + 0x64) == 4) {
            ObjFreeRecursive_3bb4f0(*(s32 *)(g + 0x1C), *(s16 *)arg0, 1);
        }
        break;
    case 3:
        CharaResBuildNpc_1f3db0(arg0, arg1, arg2);
        break;
    }
}
