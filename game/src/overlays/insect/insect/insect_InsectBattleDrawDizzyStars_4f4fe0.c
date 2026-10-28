/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawDizzyStars_4f4fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F4FE0 -- 696 bytes, 174 instructions, 29 calls.
 * Draws every live slot entry through a display handle.  The 16-byte clear at
 * $29+0xC0 is the same written-out `sb` do-while as insect_InsectBattleCamTargetToCell_4f2ff0.
 */

typedef struct Ent {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
} Ent;

typedef struct Slot {
    u8 pad00[0x994];
} Slot;

typedef struct Obj {
    u8   pad00[0xC0];
    s32  fC0;                       /* +0xC0 */
    u8   padC4[0x870 - 0xC4];
    s32  f870;                      /* +0x870 */
    u8   pad874[0x35F8 - 0x874];
    Slot f35F8[2];                  /* +0x35F8 */
    u8   pad4920[0x5D90 - 0x4920];
    f32  f5D90;                     /* +0x5D90 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/


/*rgp*/

void insect_InsectBattleDrawDizzyStars_4f4fe0(Obj *o)
{
    f32  v0[4] __attribute__((aligned(16)));
    f32  v1[4] __attribute__((aligned(16)));
    f32  v2[4] __attribute__((aligned(16)));
    f32  v3[4] __attribute__((aligned(16)));
    f32  v4[4] __attribute__((aligned(16)));
    s32  h;
    s32  i;
    Slot *sl;
    s32  j;
    Ent *e;
    s32  t;
    u8  *p;
    u32  n;
    f32  ang;
    f32  cs;
    f32  sn;

    ang = (3.1415927f * o->f5D90) / 180.0f;
    cs = Sinf_128fd0(ang);
    sn = -Cosf_128d30(ang);
    DrawListAddTexLoad_1418c0(o->fC0, 0x2A6, 1.0f);
    h = ((s32)DrawListBeginPrim_141b00(o->fC0));
    GsPktSetAlphaBlend_13e500(h, 1);
    GsPktSetBlendMode_13e4f0(h, 1);
    GsPktSetAlphaTestFunc_13e4c0(h, 6, 0);
    GsPktEnableAlphaTest_13e4d0(h, 1);
    GsPktEnableZTest_13e460(h, 0);
    GsPktSetGouraud_13e3b0(h, 1);
    GsPktSetTexFilter_13e3d0(h, 0);
    GsPktSetAntialias_13e390(h, 0);
    GsPktEnableZTest_13e460(h, 1);
    GsPktSetZTest_13e450(h, 2);
    GsPktSetZWriteMask_13e430(h, 0);
    GsPktSetOriginMode_13e2f0(h, 0);
    GsPktSetTextured_13e400(h, 1);
    GsPktSetUseUV_13e3e0(h, 1);
    for (i = 0; i < 2; i++) {
        sl = &o->f35F8[i];
        for (j = 0; j < 5; j++) {
            e = ((Ent *)insect_InsectTeamGetPiece_5138d0(sl, j));
            if (e != 0) {
                if (insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                    if (insect_InsectPieceIsDizzy_514c10(e) != 0) {
                        p = (u8 *)v0;
                        n = 0x10;
                        if (p != 0) {
                            do {
                                *p = 0;
                                n--;
                                p++;
                            } while (n != 0);
                        }
                        t = ((s32)ObjRecGetLiveObject_1c4a90(o->f870, e->f6C));
                        if (t != 0) {
                            ObjGetAttachNodePos_1adec0(t, 0, v0);
                            v0[1] = v0[1] + 1.5f;
                        }
                        insect_InsectBattleCalcQuadCorners_4f47a0(o, v1, v2, v3, v4, v0, 0, 1, 1.0f, 1.0f, cs, sn, 0.0f, 0.0f
);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v1);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v2);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v3);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v4);
                    }
                }
            }
        }
    }
    DrawListEndPrim_141a20(o->fC0);
}
