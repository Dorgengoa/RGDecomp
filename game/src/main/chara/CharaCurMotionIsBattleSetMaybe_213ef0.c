/* rgp:protos */
#define RGP_SELF_CharaCurMotionIsBattleSetMaybe_213ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 CharaCurMotionIsBattleSetMaybe_213ef0(u8 *a0)
{
    s32 code;
    void *ret = CharaGetCurMotionName_238560(a0);
    u8 *v3 = *(u8 **)(a0 + 0x3f4);

    if (v3 == 0 || ret == 0) {
        code = -1;
    } else {
        s32 pos[3];
        s32 p3c, p38;

        pos[0] = *(s32 *)(v3 + 0x1f0);
        pos[1] = *(s32 *)(v3 + 0x1f4);
        pos[2] = *(s32 *)(v3 + 0x1f8);
        MotionListFindByName_1721d0(pos, ret, &p3c, &p38);
        code = p38;
    }
    return code == 0x32;
}
