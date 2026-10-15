#include "types.h"
/* normal 0x005233C0 -- the 0x1E-widget phase handler's CLOSE half, the direct
 * sibling of src/wf/normal/normal_InsectEntryNoFundsMsgOpenState_523450.c: same static widget
 * D_005281A0, same id 0x1E, same small-data D_004849A8 tail post.
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  The guarded block
 * is one func_290690 with (0.0f, pool literal, -1.0f).  The tail test is
 * `c.le.s $f0,$f1` against an inline 0.0f with `bc1fl` PAST the block, so the
 * source test is written `<= 0.0f` and the block is the fall-through side --
 * the opposite polarity to the seed's `>= 1.0f`.
 * `addiu $4,$28,-0x7C8` is the ADDRESS of the small-data object D_004849A8.
 */

extern u8    D_005281A0[];

extern f32   D_0047D7D0;          /* gp - 0x79A0 */
extern s32   D_004849A8;          /* gp - 0x7C8  */

extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *w, u16 id);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_InsectEntryNoFundsMsgCloseState_5233c0(void *a, s32 b)
{
    if (b != 0) {
        func_290690(D_005281A0, 0x1E, 0.0f, D_0047D7D0, -1.0f);
    }
    if (func_290770(D_005281A0, 0x1E) <= 0.0f) {
        func_291110(D_005281A0, 0x1E, 0, 1);
        func_28EDE0(&D_004849A8, 0x7532, 1);
    }
    return 1;
}
