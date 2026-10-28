/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawStarSprite_4f4e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F4E10 -- 456 bytes, 114 instructions.
 * Draws the 0x100-wide box centred on the point func_15D160 resolves. */

typedef struct Obj {
    u8  pad00[0xD4];
    s32 fD4;                        /* +0xD4 */
} Obj;

typedef struct Vec {
    s32 x;
    s32 y;
    s32 z;
} Vec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleDrawStarSprite_4f4e10(Obj *a, void *b, s32 c)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Vec)]; char m1[0x10]; })];
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 z;

    if (ProjectToScreenOffset_15d160(&(*(Vec *)(rgp_blk1 + 0x0)), c) != 0) {
        GsPktOpenPrim_13f730(b, 6);
        GsPktSetTexture_13ec00(b, a->fD4);
        z = (*(Vec *)(rgp_blk1 + 0x0)).z;
        x0 = (*(Vec *)(rgp_blk1 + 0x0)).x - 0x80;
        x1 = (*(Vec *)(rgp_blk1 + 0x0)).x + 0x80;
        y0 = (*(Vec *)(rgp_blk1 + 0x0)).y - 0x80;
        y1 = (*(Vec *)(rgp_blk1 + 0x0)).y + 0x80;
        {
            f32 p[4] __attribute__((aligned(16))) = {0};
            p[0] = (f32)x0;
            p[2] = (f32)(*(Vec *)(rgp_blk1 + 0x0)).z;
            p[1] = (f32)y0;
            {
                f32 q[4] __attribute__((aligned(16))) = {0};
                q[0] = (f32)x1;
                q[2] = (f32)(*(Vec *)(rgp_blk1 + 0x0)).z;
                q[1] = (f32)y1;
                if (ScreenPointInBounds_15d4a0(p) == 0 || ScreenPointInBounds_15d4a0(q) == 0) {
                    return;
                }
                                GsPktSetRGBAQ_13ee40(b, 0x80, 0x80, 0x80, 0x80);
                                GsPktSetUV_13ed60(b, 0x41, 1);
                                GsPktSetXYZ_13ef10(b, x0, y0, z);
                                GsPktSetUV_13ed60(b, 0x7F, 0x3E);
                                GsPktSetXYZ_13ef10(b, x1, y1, z);
                                GsPktClose_13f5b0(b);
            }
        }
    }
}
