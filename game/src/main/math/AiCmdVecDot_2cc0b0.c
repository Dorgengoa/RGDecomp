/* rgp:protos */
#define RGP_SELF_AiCmdVecDot_2cc0b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct B2cc0b0 { u8 d[0x30]; };

/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdVecDot_2cc0b0(struct B2cc0b0 *p, s32 kind)
{ RG_VU0_FRAME;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    __attribute__((aligned(16))) unsigned char rgp_blk2[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];

    if (kind != 7) {
        return 0;
    }
    ScriptSlotsToVec4_2cc920((*(f32 (*)[3])(rgp_blk1 + 0x0)), p);
    ScriptSlotsToVec4_2cc920((*(f32 (*)[3])(rgp_blk2 + 0x0)), (u8 *)p + 0x18);
    p = (struct B2cc0b0 *)((u8 *)p + 0x30);
    ScriptSlotStoreFloatRef_2cc8e0(p, Vu0InnerProduct_13bd60((*(f32 (*)[3])(rgp_blk1 + 0x0)), (*(f32 (*)[3])(rgp_blk2 + 0x0))));
    return 1;
}
