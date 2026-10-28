/* rgp:protos */
#define RGP_SELF_normal_HelpMenuPageState_521e20 1
#include "port/game_protos.h"
#line 1
/* === MATCH.  normal 0x00521E20, 162 words, byte-identical (lane nc32f,
 * session 32).  Closed on ONE edit from the two-bad park:
 *   func_28EDE0 takes THREE arguments and the third one here is 1.
 *
 * The park residue was exactly:
 *   0x00521F60  ours 24020001 li $2,1       retail 24060001 li $6,1
 *   0x00521F64  ours 5602001A bnel $16,$2   retail 5606001A bnel $16,$6
 * i.e. the constant 1 of `if (m == 1)` sat in $v0 for us and in $a2 for
 * retail.  MECHANISM: a compare constant lands in $a2 exactly when its vreg
 * is COALESCED WITH A CALL ARGUMENT in the region the compare dominates.
 * Corpus proof, two merged units: insect_InsectBattleLoadPreviewModel_4f7ea0 0x004F7F58
 * (li $6,1 / beql $16,$6, and the target block calls func_0050d7a0 with NO
 * $6 setup) and factory_FactoryBlueprintShowRecipe_4f9380 0x004F96F4 (same shape into
 * func_290010).  Here NO call sits between 0x00521F60 and any of the three
 * func_28EDE0 sites (0x00521FB0, 0x00521FC0, 0x00521FDC), none of which
 * sets $6 -- so all three inherit the 1 materialised for the compare and
 * the third argument costs ZERO words.
 * The s31 park had rejected the three-argument signature after measuring a
 * third argument of ZERO, which costs one `daddu $6,$0,$0` per site (three
 * sites).  The value of the argument was the whole lever.  Every merged
 * caller of func_28EDE0 in the tree declares it (void*, s32, s32).
 *
 * Everything else from the s31 park stands: pi IS a .lit4 pool entry and
 * MUST be written as the literal (as an extern the three loads CSE into one
 * and the unit is 2 words short); the row test is
 * D_004849E8[D_004849F8].f04 > D_004849FC with the array on the LEFT. */
#include "types.h"
/* normal 0x00521E20 -- the shop hint banner: the open pass re-arms the 0x32 /
 * 0x33 widgets, then every frame the 0x00484A00 phase is walked by
 * D_004807C0 (a +/-1.0f direction flag) and reflected back as the 0x33 alpha.
 * `sw $2,-0x49B0` with $2 = lui 0x3F800000 is an f32 store of a CONSTANT
 * through a GPR -- one materialisation, one store.
 * The `adda.s`/`madd.s` is retail's own contraction of `p + 2.0f * (A * dir)`,
 * so the product stays inline. */

extern u8 D_004B2570;
extern u8 normal_D_00528180[];
extern u8 normal_D_005281A0[];
extern u8 normal_D_005281C0[];

typedef struct Row { u8 pad00[4]; s16 f04; u8 pad06[0x76 - 0x06]; } Row;

extern f32   D_0047D3FC;          /* gp - 0x7D74 */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047D7C4;          /* gp - 0x79AC */
extern f32   D_0047D7CC;          /* gp - 0x79A4 */
extern f32   D_0047D7D0;          /* gp - 0x79A0 */
extern f32   D_004807C0;          /* gp - 0x49B0 */
extern void *D_004849A8;          /* gp - 0x7C8  */
extern Row  *D_004849E8;          /* gp - 0x788  */
extern s16   D_004849F8;          /* gp - 0x778  */
extern u8    D_004849FC;          /* gp - 0x774  */
extern f32   D_00484A00;          /* gp - 0x770  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_HelpMenuPageState_521e20(void *a, s32 b)
{
    s32 m;
    f32 v;
    f32 t;

    if (b != 0) {
        UiSetWidgetsVisibleById_291110(normal_D_005281A0, 0x32, 1, 1);
        UiSetWidgetAlpha_2907a0(normal_D_005281A0, 0x32, 0.0f);
        UiFadeWidgetAlpha_290690(normal_D_005281A0, 0x32, 1.0f, D_0047D7CC, -1.0f);
        UiSetWidgetPos_290f60(normal_D_005281A0, 0x32, 0x100, 0);
        UiMoveWidgetUniform_290f50(normal_D_005281A0, 0x32, 0, 0, D_0047D7C4, 0);
        UiSetWidgetsVisibleById_291110(normal_D_005281A0, 0x33, 1, 1);
        UiSetWidgetAlpha_2907a0(normal_D_005281A0, 0x33, 0.0f);
        UiFadeWidgetAlpha_290690(normal_D_005281A0, 0x33, 1.0f, D_0047D7CC, -1.0f);
        UiFadeWidgetAlpha_290690(normal_D_00528180, 0x28, 0.0f, D_0047D7D0, -1.0f);
        D_00484A00 = 0.0f;
        D_004807C0 = 1.0f;
    }
    m = MenuGridCursorInput_28e170(normal_D_005281C0, &D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(normal_D_005281C0);
    if (m == 1) {
        D_004849FC = D_004849FC + 1;
        if (D_004849E8[D_004849F8].f04 > D_004849FC) {
            StateMachineSetState_28ede0(&D_004849A8, 0x753D, 1);
        } else {
            StateMachineSetState_28ede0(&D_004849A8, 0x753C, 1);
        }
    } else if (m == 2) {
        StateMachineSetState_28ede0(&D_004849A8, 0x753C, 1);
    }
    v = D_00484A00 + 2.0f * (D_0047D3FC * D_004807C0);
    D_00484A00 = v;
    if (v > 3.1415927f || v < 0.0f) {
        if (v > 3.1415927f) {
            D_00484A00 = 3.1415927f;
        } else {
            D_00484A00 = 0.0f;
        }
        D_004807C0 = D_004807C0 * -1.0f;
    }
    t = D_0047D5D0 + D_00484A00 / 3.1415927f;
    if (t > 1.0f) {
        t = 1.0f;
    }
    UiSetWidgetAlpha_2907a0(normal_D_005281A0, 0x33, t);
    return 1;
}
