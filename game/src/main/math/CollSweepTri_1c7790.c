/* rgp:protos */
#define RGP_SELF_CollSweepTri_1c7790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CollSweepTri_1c7790(u8 *o, s32 a, s32 b, s32 c)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    __attribute__((aligned(16))) unsigned char rgp_blk2[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];
    u8 r;

    TriCalcBounds_1cb540((*(f32 (*)[3])(rgp_blk1 + 0x0)), (*(f32 (*)[3])(rgp_blk2 + 0x0)), a, b, c);
    if ((*(f32 (*)[3])(rgp_blk1 + 0x0))[0] < *(f32 *)(o + 0x50) || (*(f32 (*)[3])(rgp_blk1 + 0x0))[1] < *(f32 *)(o + 0x54) || (*(f32 (*)[3])(rgp_blk1 + 0x0))[2] < *(f32 *)(o + 0x58)) return 0;
    if (!((*(f32 (*)[3])(rgp_blk2 + 0x0))[0] <= *(f32 *)(o + 0x60)) || !((*(f32 (*)[3])(rgp_blk2 + 0x0))[1] <= *(f32 *)(o + 0x64)) || !((*(f32 (*)[3])(rgp_blk2 + 0x0))[2] <= *(f32 *)(o + 0x68))) return 0;
    r = CollSweepTriFace_1c7950(o, a, b, c) != 0;
    r = (r | CollSweepTriEdge_1c7bf0(o, a, b)) != 0;
    r = (r | CollSweepTriEdge_1c7bf0(o, b, c)) != 0;
    r = (r | CollSweepTriEdge_1c7bf0(o, c, a)) != 0;
    r = (r | CollSweepTriVertex_1c7f30(o, a)) != 0;
    r = (r | CollSweepTriVertex_1c7f30(o, b)) != 0;
    r = (r | CollSweepTriVertex_1c7f30(o, c)) != 0;
    return r;
}
