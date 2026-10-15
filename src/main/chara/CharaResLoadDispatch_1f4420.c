#include "types.h"

s32 CharaResBuildMon_1f3860(u8 *, s32, s32);
s32 CharaResBuildNpc_1f3db0(u8 *, s32, s32);
s32 CharaResBuildPcWithWeapons_1f4050(u8 *, s32);
u8 *GetGameData_1fede0(void);
s32 ObjFreeRecursive_3bb4f0(s32, s32, s32);

void CharaResLoadDispatch_1f4420(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *g;
    s32 k;

    g = GetGameData_1fede0();
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
