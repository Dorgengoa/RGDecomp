/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuOpponentIntro_501c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00501C60 -- 908 bytes, 227 instructions, 41 calls, 10 conditional
 * branches, br/ins 0.044.  insect_InsectBattleGetStep_50d6a0(o, 2) state dispatch family;
 * header is insect_InsectBattleMenuTeamSelect_5004f0.c.  Compare chain 0xB, 0x11, 1, so source
 * order is 1, 0x11, 0xB, and case 1 FALLS THROUGH into 0x11.
 *
 * D_0047DADC is a MAIN-image gp float (_gp - 0x7694) and must stay non-const
 * to keep %gp_rel.
 *
 * `0x54 - n * 8 / 2` is written out, not folded to `n * 4`: retail emits
 * sll 3 then the bgez/addiu/sra signed divide-by-two, which only appears if
 * the source really divides.  n is SIGNED even though func_134BB0 returns u32
 * -- an unsigned n gives a bare srl and loses three words.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x3F8C - 0x880];
    u8    f3F8C[0x5054 - 0x3F8C];   /* +0x3F8C */
    u8    f5054[0x5DA0 - 0x5054];   /* +0x5054 */
    s32   f5DA0;                /* +0x5DA0 */
    u8    pad5DA4[0x4];
    s32   f5DA8;                /* +0x5DA8 */
    u8    pad5DAC[0x5EFE - 0x5DAC];
    s16   f5EFE;                /* +0x5EFE */
} Ins;

typedef struct Rec { u8 pad00[0x5C]; const char *f5C; } Rec;

extern f32 D_0047DADC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern u32   strlen(const char *t);
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

void insect_InsectBattleMenuOpponentIntro_501c60(Ins *o)
{
    void *g;
    void *p;
    void *w;
    Rec  *r;
    const char *t;
    s32  n;
    s32  i;

    g = o->f5054;
    p = o->f3F8C;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectBattleSetStep_50d7a0(o, 0x11, 2, -1);
        /* fallthrough */
    case 0x11:
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC394, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC39B, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC378, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f87C, 0xC37E, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0x7565, 0.0f);
        UiSetWidgetVisible_290010(o->f878, 0x7565, 0, -1);
        UiSetWidgetAlpha_2907a0(o->f878, 0x755F, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0x753E, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0x753C, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0x7546, 0.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0x7530, 1.0f);
        UiSetWidgetAlpha_2907a0(o->f878, 0xC38F, 0.0f);
        InsectUiStageCaptionLayoutMaybe_393fc0(g, UiFindWidget_290460(o->f878, 0x7532), o->f5EFE);
        InsectBattleMenuFrameNineSliceMaybe_393ac0(g, UiFindWidget_290460(o->f878, 0x7535), 0xA8, 0x24, 2);
        InsectBattleMenuFrameNineSliceMaybe_393ac0(g, UiFindWidget_290460(o->f878, 0x7539), 0xA0, 0x94, 0);
        w = UiFindWidget_290460(o->f878, 0x753A);
        InsectUiTeamIconRowLayoutMaybe_393820(g, w, 0x1C, 1, insect_InsectTeamFindKing_513840(p));
        if (o->f5DA8 == 5) {
            UiSetWidgetAlpha_2907a0(o->f878, 0x753A, 0.0f);
        }
        UiSetWidgetPos_290f60(o->f878, 0x7534, o->f5DA0 + 0x100, 0x4A);
        UiMoveWidgetUniform_290f50(o->f878, 0x7534, o->f5DA0 - 0xC2, 0x4A, 0.5f, 0);
        UiSetWidgetAlpha_2907a0(o->f878, 0x7534, 0.0f);
        UiFadeWidgetAlpha_290690(o->f878, 0x7534, 1.0f, D_0047DADC, -1.0f);
        if (insect_InsectBattleTestFlag_50da40(o, 2) == 0) {
            n = 0;
            t = ((const char *)insect_InsectTeamGetName_5138b0(p));
            if (t != 0) {
                n = strlen(t);
            }
            UiSetTextPos_28f5d0(o->f878, 0x7535, 0x54 - n * 8 / 2, 8, 0);
            UiSetTextString_28f510(o->f878, 0x7535, ((const char *)insect_InsectTeamGetName_5138b0(p)), 0);
            i = 0;
            do {
                r = ((Rec *)insect_InsectTeamGetPiece_5138d0(p, i));
                if (r != 0) {
                    UiSetTextString_28f510(o->f878, 0x753A, r->f5C, i);
                }
                i++;
            } while (i < 5);
        }
        if (insect_InsectBattleTestFlag_50da40(o, 2) == 0) {
            UiSetWidgetVisible_290010(o->f878, 0x7534, 1, -1);
        }
        UiSetWidgetVisible_290010(o->f87C, 0xC393, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        break;
    case 0xB:
        insect_InsectBattleSetState_50d8c0(o, 0, 2, -1);
        break;
    }
}
