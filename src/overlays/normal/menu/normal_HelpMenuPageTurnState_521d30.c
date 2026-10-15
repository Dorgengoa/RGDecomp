#include "types.h"
/* normal 0x00521D30 -- the 0x32/0x33 caption pair on the STATIC widget
 * D_005281A0 (same family as normal_InsectEntryNoFundsMsgOpenState_523450).  f(void *, s32), `$4`
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

extern u8 D_005281A0[];

extern f32   D_0047D7C4;          /* gp - 0x79AC */
extern f32   D_0047D7C8;          /* gp - 0x79A8 */
extern s32   D_004849A0;          /* gp - 0x7D0  */
extern s32   D_004849A8;          /* gp - 0x7C8  */
extern s32   D_004849E0;          /* gp - 0x790  */

extern void  func_14D830(s32 a);
extern void  func_158AC0(s32 a, s32 b);
extern s32   func_15DE40(void);
extern void  func_1CD340(s32 a, s32 b);
extern s32   func_1F59D0(void);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *p, u16 id);
extern void  func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_HelpMenuPageTurnState_521d30(void *a, s32 b)
{
    s32 g;

    if (b != 0) {
        func_290690(D_005281A0, 0x32, 0.0f, D_0047D7C8, -1.0f);
        func_290F50(D_005281A0, 0x32, 0x200, 0, 0, D_0047D7C4);
        func_290690(D_005281A0, 0x33, 0.0f, D_0047D7C8, -1.0f);
    }
    if (func_290770(D_005281A0, 0x32) <= 0.0f) {
        func_158AC0(func_15DE40(), 0x32C);
        g = func_1F59D0();
        if (D_004849E0 > 0) {
            func_1CD340(g, D_004849E0);
        }
        func_14D830(D_004849A0);
        func_28EDE0(&D_004849A8, 0x753A, 1);
    }
    return 1;
}
