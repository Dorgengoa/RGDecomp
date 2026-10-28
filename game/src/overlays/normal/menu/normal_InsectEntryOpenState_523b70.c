/* rgp:protos */
#define RGP_SELF_normal_InsectEntryOpenState_523b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00523B70 -- the six-row party roster panel's one-shot build: the
 * 0x01/0x02/0x03/0x11 frame widgets, then one pass over the six rows laying out
 * the 0x04+i portrait and the 0x0A+i label and colouring each by the roster
 * state in D_004807C4.
 *
 * `$4` is never read -- another member of the f(void *, s32) state-handler
 * family (see normal_HelpMenuOpenState_522880, whose widget group this one sits beside).
 * The `andi $rX, $rY, 0xFFFF` before every row call is the widget id's u16
 * parameter written `idA` at each site; mwcc CSEs the mask into $19
 * and $18 because there are five sites, not one.
 * `mult1` is mwcc using the R5900's SECOND multiplier for the independent
 * f12*f06 product -- compiler output, not source.
 * `dsll32 $2,$2,16 / dsra32 $2,$2,16` on the just-stored value is the s16 field
 * read back through mwcc's store forwarding, so the expression names r->f02
 * rather than the local it was computed in.
 * The k==6 / k==7 chain carries the NEXT GUARD'S CONSTANT in its `bnel` delay
 * slot, which is the discriminator for an if/else-if chain and not a switch. */

extern u8 normal_D_00528180;
extern u8 normal_D_005281C0;

extern f32 D_0047D5D0;            /* gp - 0x7BA0 */
extern s32 D_004807C4;            /* gp - 0x49AC */
extern s32 D_004849A8;            /* gp - 0x7C8  */
extern s32 D_004849B4;            /* gp - 0x7BC  */
extern s32 D_004849D0;            /* gp - 0x7A0  */
extern s32 D_004849D4;            /* gp - 0x79C  */
extern u8  D_004849D8;            /* gp - 0x798  */

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x0A - 0x08];
    s16 f0A;
    u8  pad0C[0x10 - 0x0C];
    s16 f10;
    s16 f12;
} Box;

typedef struct Obj  { u8 pad00[4]; Box box; } Obj;
typedef struct Fld  { u8 pad00[4]; s32 f04; } Fld;
typedef struct Wgt  { u8 pad00[0x20]; s32 f20; u8 pad24[4]; Fld *f28; } Wgt;
typedef struct Wld  { u8 pad000[0x160]; s64 f160; } Wld;
typedef struct Ctx  { u8 pad00[0x10]; void *f10; u8 pad14[4]; Wld *f18; } Ctx;

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

s32 normal_InsectEntryOpenState_523b70(void *a, s32 b)
{
    Obj *o;
    Box *r;
    Ctx *ctx;
    Wgt *w;
    Fld *fp;
    s32  t;
    s32  k;
    /* DECLARATION ORDER IS LOAD-BEARING and this is the whole 36-word residue:
     * retail is n=$20 idA=$19 idB=$18 i=$17, and later in this list means a
     * LOWER register.  All 24 permutations were enumerated; this is the only
     * byte-identical one (next best 11). */
    s32  n;
    s32  idA;
    s32  idB;
    s32  i;

    if (b != 0) {
        ctx = ((Ctx *)GetGameData_1fede0());
        if (ctx == 0) {
            return 0;
        }
        D_004807C4 = ((short)StateVarGet_3ccac0(ctx->f10, 5)) - 1;
        if (D_004807C4 < 0) {
            D_004807C4 = 0;
        }
        D_004849D4 = -1;
        D_004849D0 = 1;
        UiSetWidgetsVisibleById_291110(&normal_D_00528180, 1, 1, 1);
        UiSetTextString_28f510(&normal_D_00528180, 1, MsgTableLookup_28aa30(D_004849B4, 6), 0);
        UiSetTextCenteredX_28f300(&normal_D_00528180, 1, 0x100, 0);
        UiSetWidgetPos_290f60(&normal_D_00528180, 1, 0, 0x14);
        UiSetWidgetVisible_290010(&normal_D_00528180, 3, 1, -1);
        UiSetWidgetPos_290f60(&normal_D_00528180, 3, 0x84, 0x78);
        UiSetWidgetsVisibleById_291110(&normal_D_00528180, 2, 1, 1);
        UiSetWidgetVisible_290010(&normal_D_00528180, 0x11, 1, -1);
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x11, 0xFE, 0x146);
        UiSetWidgetAlpha_2907a0(&normal_D_00528180, 1, 0.0f);
        UiSetWidgetAlpha_2907a0(&normal_D_00528180, 3, 0.0f);
        UiSetWidgetAlpha_2907a0(&normal_D_00528180, 2, 0.0f);
        UiSetWidgetAlpha_2907a0(&normal_D_00528180, 0x11, 0.0f);
        UiFadeWidgetAlpha_290690(&normal_D_00528180, 1, 1.0f, D_0047D5D0, -1.0f);
        UiFadeWidgetAlpha_290690(&normal_D_00528180, 3, 1.0f, D_0047D5D0, -1.0f);
        UiFadeWidgetAlpha_290690(&normal_D_00528180, 2, 1.0f, D_0047D5D0, -1.0f);
        UiFadeWidgetAlpha_290690(&normal_D_00528180, 0x11, 1.0f, D_0047D5D0, -1.0f);
        o = ((Obj *)UiEntryListFindByTag_28ea40(&normal_D_005281C0, 0x7531));
        o->box.f12 = 0;
        r = &o->box;
        n = D_004807C4;
        if (n >= 6) {
            r->f12 = 0;
            n = 5;
        }
        r->f0A = n;
        r->f02 = (5 - n) * 0x1B;
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x10, r->f00 + r->f10 * r->f04 - 0x1A,
                    r->f02 + r->f12 * r->f06 + 6);
        w = ((Wgt *)UiFindWidget_290460(&normal_D_00528180, 3));
        if (w == 0) {
            return 0;
        }
        t = w->f20;
        if (t == 0) {
            return 0;
        }
        UiLayoutWindowFrame_28b8e0(t, 0xFA, 0xAA, 6);
        w = ((Wgt *)UiFindWidget_290460(&normal_D_00528180, 0x11));
        if (w == 0) {
            return 0;
        }
        t = w->f20;
        if (t == 0) {
            return 0;
        }
        UiLayoutFrameRectsMaybe_28bbb0(t, 0x80, 0x24);
        i = 0;
        D_004849D8 = 1;
        do {
            idA = (u16)(i + 4);
            idB = (u16)(i + 0xA);
            w = ((Wgt *)UiFindWidget_290460(&normal_D_00528180, idA));
            if (w != 0) {
                fp = w->f28;
                if (fp != 0) {
                    fp->f04 = MsgTableLookup_28aa30(D_004849B4, i);
                    UiSetWidgetPos_290f60(&normal_D_00528180, idA, 6, i * 0x1B + 8);
                    UiSetTextColor_290a40(&normal_D_00528180, idA, 0xFF303030, 0);
                    UiSetSpriteUvRect_28f9d0(&normal_D_00528180, idA, 0x76, 0x6C, 0x14,
                                0x14, 0);
                    UiSetWidgetColor_2905b0(&normal_D_00528180, idB, 1.0f, 1.0f, 1.0f,
                                -1.0f);
                    UiSetWidgetSubItemValue_291250(&normal_D_00528180, idB, 0,
                                normal_InsectEntryGetFee_524220(6 - i));
                    k = D_004807C4;
                    if (k >= 6) {
                        if (k == 6 && i == 0) {
                            UiSetTextColor_290a40(&normal_D_00528180, idA, 0xFF007F7F,
                                        0);
                        } else if (k == 7 && i == 0) {
                            UiSetTextColor_290a40(&normal_D_00528180, idA, 0xFF007F7F,
                                        0);
                            UiSetSpriteUvRect_28f9d0(&normal_D_00528180, idA, 0x8A, 0x6C,
                                        0x14, 0x14, 0);
                        } else {
                            UiSetSpriteUvRect_28f9d0(&normal_D_00528180, idA, 0x8A, 0x6C,
                                        0x14, 0x14, 0);
                        }
                    } else if (5 - i < n) {
                        UiSetSpriteUvRect_28f9d0(&normal_D_00528180, idA, 0x8A, 0x6C,
                                    0x14, 0x14, 0);
                    } else if (n < 5 - i) {
                        UiSetTextColor_290a40(&normal_D_00528180, idA, 0xFF202020, 0);
                        UiSetWidgetColor_2905b0(&normal_D_00528180, idB, 0.5f, 0.5f,
                                    0.5f, -1.0f);
                    }
                }
            }
            i++;
        } while (i < 6);
        i = 5 - D_004807C4;
        if (i < 0) {
            i = 0;
        }
        UiSetSpriteW_28fbf0(&normal_D_00528180, 3, 0, r->f12 + 4 + i);
        UiSetSpriteUvW_28f850(&normal_D_00528180, 3, 0, r->f12 + 4 + i);
        UiSetWidgetPos_290f60(&normal_D_00528180, 2, 0x84, (r->f12 + i) * 0x1B + 0x78);
        UiSetWidgetSubItemValue_291250(&normal_D_00528180, 0x14, 0, ctx->f18->f160);
    }
    if (UiGetWidgetAlpha_290770(&normal_D_00528180, 3) >= 1.0f) {
        StateMachineSetState_28ede0(&D_004849A8, 0x7532, 1);
    }
    return 1;
}
