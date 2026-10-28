/* rgp:protos */
#define RGP_SELF_ScriptCmdVecDot_334160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct B334160 { u8 d[0x30]; };

/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdVecDot_334160(struct B334160 *p, s32 kind)
{ RG_VU0_FRAME;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    __attribute__((aligned(16))) unsigned char rgp_blk2[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];

    if (kind != 7) {
        return 0;
    }
    ScriptSlotsToVec4_334810((*(f32 (*)[3])(rgp_blk1 + 0x0)), p);
    ScriptSlotsToVec4_334810((*(f32 (*)[3])(rgp_blk2 + 0x0)), (u8 *)p + 0x18);
    p = (struct B334160 *)((u8 *)p + 0x30);
    ScriptSlotStoreFloatRef_3347d0(p, Vu0InnerProduct_13bd60((*(f32 (*)[3])(rgp_blk1 + 0x0)), (*(f32 (*)[3])(rgp_blk2 + 0x0))));
    return 1;
}
