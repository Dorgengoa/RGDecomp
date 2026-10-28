/* rgp:protos */
#define RGP_SELF_EvCmdVecNormalize_25df70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} F4;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdVecNormalize_25df70(s64 *arg0, s32 arg1) {
    F4 v __attribute__((aligned(16)));

    switch (arg1) {
    case 3:
        v.x = *(f32 *)(*(u8 **)((u8 *)arg0 + 4) + 4);
        v.y = *(f32 *)(*(u8 **)((u8 *)arg0 + 0xC) + 4);
        v.z = *(f32 *)(*(u8 **)((u8 *)arg0 + 0x14) + 4);
        v.w = 1.0f;
        break;
    case 6:
        ScriptArgsToVec4_26a220(&v, (u8 *)arg0 + 0x18);
        break;

    default:
        return 0;
    }
    VecNormalize_13bd90(&v, &v);
    ScriptSetRefFloat_26a1c0(arg0++, v.x);
    ScriptSetRefFloat_26a1c0(arg0++, v.y);
    ScriptSetRefFloat_26a1c0(arg0, v.z);
    return 1;
}
