/* rgp:protos */
#define RGP_SELF_ModelObjApplyMotionList_186700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void ModelObjApplyMotionList_186700(void *arg0) {
    void *node;
    void *temp4;
    u8 buf[0x18] __attribute__((aligned(16)));

    node = *(void **)((u8 *)arg0 + 0x1F4);
    if (node == 0) {
        return;
    }
    while (node != 0) {
        temp4 = (u8 *)node + 0x10;
        if (temp4 != 0) {
            MotionPlayerGetBlendMaybe_172ce0(temp4, buf);
            if (!(*(s32 *)(buf + 0x0) != 0)) {
                ModelApplyMotion_171a10(arg0, *(s32 *)(buf + 0x8), *(f32 *)(buf + 0xC));
            } else {
                ModelApplyMotionBlend_171680(arg0, *(s32 *)(buf + 0x8), *(s32 *)(buf + 0x10),
                             *(f32 *)(buf + 0xC), *(f32 *)(buf + 0x14), *(f32 *)(buf + 0x4));
            }
        }
        node = *(void **)node;
    }
}
