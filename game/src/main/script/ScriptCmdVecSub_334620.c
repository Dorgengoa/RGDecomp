/* rgp:protos */
#define RGP_SELF_ScriptCmdVecSub_334620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 ScriptCmdVecSub_334620(u8 *p, s32 kind)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];

    if (kind != 6) {
        return 0;
    }
    ScriptSlotsToVec4_334810((*(f32 (*)[3])(rgp_blk1 + 0x0)), p + 0x18);
    ScriptSlotStoreFloatRef_3347d0(p, *(f32 *)(*(s32 *)(p + 0x4) + 4) - (*(f32 (*)[3])(rgp_blk1 + 0x0))[0]);
    ScriptSlotStoreFloatRef_3347d0(p + 8, *(f32 *)(*(s32 *)(p + 0xC) + 4) - (*(f32 (*)[3])(rgp_blk1 + 0x0))[1]);
    ScriptSlotStoreFloatRef_3347d0(p + 0x10, *(f32 *)(*(s32 *)(p + 0x14) + 4) - (*(f32 (*)[3])(rgp_blk1 + 0x0))[2]);
    return 1;
}
