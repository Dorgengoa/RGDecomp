/* rgp:protos */
#define RGP_SELF_AnimSlotApplyToFrame_154580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void AnimSlotApplyToFrame_154580(u8 *a, u8 *b)
{
    u8 buf[0x40] __attribute__((aligned(16)));

    if (*(s32 *)(a + 0xc) != 0) {
        FrameSetScale_14a2c0(b, a + 0x40);
    }

    if (*(s32 *)(a + 0x0) != 0) {
        ModelFrameSetRotQuat_14a130(b, a + 0x50);
    } else if (*(s32 *)(a + 0x4) != 0) {
        MtxIdentity_13d2e0(buf);
        MatRotateVu0_13bc20(buf, a + 0x30);
        ModelFrameSetRotMatrix_14a160(b, buf);
    }

    if (*(s32 *)(a + 0x8) != 0) {
        *(f32 *)(b + 0x90) = *(f32 *)(a + 0x20);
        *(f32 *)(b + 0x94) = *(f32 *)(a + 0x24);
        *(f32 *)(b + 0x98) = *(f32 *)(a + 0x28);
        FrameSetDirty_14a5e0(b);
    }

    if (*(s32 *)(a + 0x10) != 0) {
        *(u8 *)(b + 0x24) = *(s32 *)(a + 0x14);
    }
}
