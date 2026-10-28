/* rgp:protos */
#define RGP_SELF_title_FUN_004ea5f0_place 1
#define RGP_SELF_title_TitleDemoMenuIntro_4ea5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EA5F0 -- the title logo's four-state entrance
 * animation, ticked once a frame.  The state lives in D_004841B0 and the four
 * arms are an if/else-if CHAIN in source order 0,1,2,3: every converted `bnel`
 * carries THE NEXT GUARD'S CONSTANT and the last guard is a plain `bne` with a
 * nop slot, which is the chain signature, not a switch's.
 *
 * The 0x65 placement block appears TWICE, in the reset prologue and in state
 * 3, and retail emits it both times, so it is a `static inline` helper -- the
 * recorded form of the cold-block recipe for a REPEATED block.
 *
 * `mult` + `mult1` are the R5900's two multiply pipelines, which is what a
 * pair of INDEPENDENT s16 products compiles to; nothing in the source says so.
 * `cvt.w.s` reaches the listing as a bare `.word`, so read that region from the
 * encodings and not from any opcode-driven instrument.
 *
 * The callees take the widget id as u16 while the loop counter is s32, which is
 * why `andi $5, $17, 0xFFFF` is re-issued at EVERY call site instead of once at
 * the assignment.
 */

typedef struct Rec_title_FUN_004ea5f0 {
    u8 pad00[0x4];
    s16 field04;
    s16 field06;
    s16 field08;
    s16 field0A;
    u8 pad0C[0x8];
    s16 field14;
    s16 field16;
} Rec_title_FUN_004ea5f0;

extern void *D_00484158;
extern void *D_0048415C;
extern void *D_00484170;
extern s32 D_004841AC;
extern s16 D_004841B0;
extern s16 D_004841B4;
extern u8 D_004841B8[3];
extern s16 D_0048418C;
extern f32 D_0047D518;
extern f32 D_0047D520;

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

static inline void title_FUN_004ea5f0_place(void)
{
    Rec_title_FUN_004ea5f0 *p;

    p = ((Rec_title_FUN_004ea5f0 *)UiEntryListFindByTag_28ea40(D_0048415C, 0x7537));
    if (p != 0) {
        UiSetWidgetPos_290f60(D_00484170, 0x65,
                    (s32)(-6.0f + (f32)(p->field04 + p->field14 * p->field08)),
                    p->field06 + p->field16 * p->field0A);
    }
}

s32 title_TitleDemoMenuIntro_4ea5f0(s32 a, s32 b)
{
    s32 sp40[4] __attribute__((aligned(16)));
    s32 sp30[4] __attribute__((aligned(16)));
    s32 i;
    s32 id;
    s32 *q;
    u8 *f;
    s16 st;

    if (b != 0) {
        title_TitleSceneOverlayModeOn_4eaa40();
        UiSetWidgetVisible_290010(D_00484170, 1, 0, -1);
        D_004841B4 = 0;
        D_004841B0 = 0;
        D_004841AC = 0;
        UiSetWidgetsVisibleById_291110(D_00484170, 0x61, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00484170, 0x61, 0.0f);
        UiFadeWidgetAlpha_290690(D_00484170, 0x61, 1.0f, D_0047D520, -1.0f);
        UiSetWidgetAlpha_2907a0(D_00484170, 0x62, 0.0f);
        UiSetWidgetPos_290f60(D_00484170, 0x62, 0x100, 0);
        UiSetWidgetAlpha_2907a0(D_00484170, 0x63, 0.0f);
        UiSetWidgetPos_290f60(D_00484170, 0x63, 0x1C8, 0);
        UiSetWidgetAlpha_2907a0(D_00484170, 0x64, 0.0f);
        UiSetWidgetPos_290f60(D_00484170, 0x64, 0x290, 0);
        UiSetWidgetAlpha_2907a0(D_00484170, 0x65, 0.0f);
        title_FUN_004ea5f0_place();
        D_004841B8[0] = 0;
        D_004841B8[1] = 0;
        D_004841B8[2] = 0;
    }
    st = D_004841B0;
    if (st == 0) {
        if (!(UiGetWidgetAlpha_290770(D_00484170, 0x61) < 1.0f)) {
            D_004841B0 = 1;
            UiFadeWidgetAlpha_290690(D_00484170, 0x61, 1.0f, D_0047D520, -1.0f);
            UiMoveWidgetUniform_290f50(D_00484170, 0x61, 0, 0, D_0047D518, 0);
            ScreenFadeIn_1cf740(GetCurrentScene_1f5be0(), 0xA);
        }
    } else if (st == 1) {
        i = 0;
        D_004841B0 = 2;
        do {
            id = i + 0x62;
            UiFadeWidgetAlpha_290690(D_00484170, id, 1.0f, D_0047D518, -1.0f);
            UiMoveWidgetUniform_290f50(D_00484170, id, 0, 0, 20.0f, 1);
            i = i + 1;
        } while (i < 3);
    } else if (st == 2) {
        i = 0;
        do {
            q = &sp40[i];
            UiGetWidgetPos_2910a0(D_00484170, i + 0x62, q, &sp30[i]);
            if (*q < 0xC8) {
                f = &D_004841B8[i];
                if (*f == 0) {
                    GameSceneSoundSlot6PlaySeVol_1d05c0(GetCurrentScene_1f5be0(), 1, 1.0f);
                    *f = 1;
                }
            }
            i = i + 1;
        } while (i < 3);
        if ((D_004841B8[0] != 0) && (D_004841B8[1] != 0) && (D_004841B8[2] != 0)
            && (sp40[0] == sp40[2])) {
            D_004841B0 = 3;
        }
    } else if (st == 3) {
        UiFadeWidgetAlpha_290690(D_00484170, 0x65, 1.0f, D_0047D520, -1.0f);
        title_FUN_004ea5f0_place();
        UiSetWidgetsVisibleById_291110(D_00484170, 0x65, 1, 1);
        UiEntryListSelectByTag_28ea90(D_0048415C, 0x7537, 0);
        StateMachineSetState_28ede0(D_00484158, 0x10, 0);
        D_0048418C = 0;
    }
    return 1;
}
