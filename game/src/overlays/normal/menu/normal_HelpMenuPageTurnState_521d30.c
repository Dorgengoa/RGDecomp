/* rgp:protos */
#define RGP_SELF_normal_HelpMenuPageTurnState_521d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00521D30 -- the 0x32/0x33 caption pair on the STATIC widget
 * normal_D_005281A0 (same family as normal_InsectEntryNoFundsMsgOpenState_523450).  f(void *, s32), `$4`
 * never read, guard on `b`, returns 1.
 *
 * TWIN of the adjacent 236-byte handler: the two listings differ in exactly
 * ONE word, the func_28EDE0 message id.
 *
 * `mtc1 $0,$f1 / c.le.s $f0,$f1 / bc1fl` is a direct `<= 0.0f` on
 * func_290770.  `blezl $5` off the gp handle is `> 0`, and the register
 * holding it is reused as argument two -- one gp read, not two.
 * `addiu $4,$28,-0x7C8` is the ADDRESS of the small-data object D_004849A8.
 */

extern u8 normal_D_005281A0[];

extern f32   D_0047D7C4;          /* gp - 0x79AC */
extern f32   D_0047D7C8;          /* gp - 0x79A8 */
extern s32   D_004849A0;          /* gp - 0x7D0  */
extern s32   D_004849A8;          /* gp - 0x7C8  */
extern s32   D_004849E0;          /* gp - 0x790  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_HelpMenuPageTurnState_521d30(void *a, s32 b)
{
    s32 g;

    if (b != 0) {
        UiFadeWidgetAlpha_290690(normal_D_005281A0, 0x32, 0.0f, D_0047D7C8, -1.0f);
        UiMoveWidgetUniform_290f50(normal_D_005281A0, 0x32, 0x200, 0, D_0047D7C4, 0);
        UiFadeWidgetAlpha_290690(normal_D_005281A0, 0x33, 0.0f, D_0047D7C8, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(normal_D_005281A0, 0x32) <= 0.0f) {
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32C);
        g = ((s32)GetLoaderMgr_1f59d0());
        if (D_004849E0 > 0) {
            LoaderReleaseById_1cd340(g, D_004849E0);
        }
        MemStackReset_14d830(D_004849A0);
        StateMachineSetState_28ede0(&D_004849A8, 0x753A, 1);
    }
    return 1;
}
