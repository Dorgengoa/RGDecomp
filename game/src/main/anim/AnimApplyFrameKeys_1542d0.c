/* rgp:protos */
#define RGP_SELF_AnimApplyFrameKeys_1542d0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK candidate on first score -- many m2c stack fields (sp94/98/9C/A0/A4/B0/B4/B8)
   were undeclared in the draft; modeled as one output struct at sp90. */
#include "types.h"

typedef struct Out {
    s32 f0;   /* sp90 */
    s32 f4;   /* sp94 */
    s32 f8;   /* sp98 */
    s32 fC;   /* sp9C */
    s32 f10;  /* spA0 */
    s32 f14;  /* spA4 */
    u8  pad18[0x8];
    f32 f30;  /* spB0 */
    f32 f34;  /* spB4 */
    f32 f38;  /* spB8 */
} Out;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AnimApplyFrameKeys_1542d0(s32 arg0, s32 arg1, f32 fparg0)
{
    void *var_17;
    void *temp_2;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Out)]; char m1[0x30 + sizeof(u8[0x10])]; char m2[0x40 + sizeof(u8[0x10])]; char m3[0x50 + sizeof(u8[0x10])]; char m4[0x60]; char m5[0x50]; char m6[0x40]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Out) <= (0x30) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x30) + sizeof(u8[0x10]) <= (0x40) && (0x30) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk2[(0x40) + sizeof(u8[0x10]) <= (0x50) && (0x40) >= 0 ? 1 : -1];
    
    
    
    u8 sp50[0x40] __attribute__((aligned(16)));

    if (arg0 == 0) {
        return 0;
    }
    var_17 = AnimResGetFrameKeyList_14bf10(arg1);
    while (var_17 != NULL) {
        temp_2 = ArrayGetChecked_152fd0(arg0, *(u16 *)((u8 *)var_17 + 4));
        if (temp_2 != NULL) {
            AnimKeyEvalFrame_155e10(&(*(Out *)(rgp_blk1 + 0x0)), var_17, fparg0);
            if ((*(Out *)(rgp_blk1 + 0x0)).fC != 0) {
                FrameSetScale_14a2c0(temp_2, (*(u8 (*)[0x10])(rgp_blk1 + 0x40)));
            }
            if ((*(Out *)(rgp_blk1 + 0x0)).f0 != 0) {
                ModelFrameSetRotQuat_14a130(temp_2, (*(u8 (*)[0x10])(rgp_blk1 + 0x50)));
            } else {
                if ((*(Out *)(rgp_blk1 + 0x0)).f4 != 0) {
                    MtxIdentity_13d2e0(sp50);
                    MatRotateVu0_13bc20(sp50, (*(u8 (*)[0x10])(rgp_blk1 + 0x30)));
                    ModelFrameSetRotMatrix_14a160(temp_2, sp50);
                }
            }
            if ((*(Out *)(rgp_blk1 + 0x0)).f8 != 0) {
                *(f32 *)((u8 *)temp_2 + 0x90) = (*(Out *)(rgp_blk1 + 0x0)).f30;
                *(f32 *)((u8 *)temp_2 + 0x94) = (*(Out *)(rgp_blk1 + 0x0)).f34;
                *(f32 *)((u8 *)temp_2 + 0x98) = (*(Out *)(rgp_blk1 + 0x0)).f38;
                FrameSetDirty_14a5e0(temp_2);
            }
            if ((*(Out *)(rgp_blk1 + 0x0)).f10 != 0) {
                *((u8 *)temp_2 + 0x24) = (s8) (*(Out *)(rgp_blk1 + 0x0)).f14;
            }
        }
        var_17 = *(void **)var_17;
    }
    return 1;
}
