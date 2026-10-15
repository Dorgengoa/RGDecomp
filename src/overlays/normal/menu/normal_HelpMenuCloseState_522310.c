#include "types.h"
/* normal 0x00522310 -- the 0x28/0x29/0x2A caption trio on the STATIC widget
 * D_00528180 (same f(void *, s32) family as normal_FUN_00521C40: `$4` never
 * read, guard on `b`, every path returns 1).
 *
 * `mtc1 $0,$f1 / c.le.s $f0,$f1 / bc1fl` is a direct `<= 0.0f` on
 * func_290770.  The two `sb $0` are gp bytes, written after the three
 * func_291110 calls.
 */

extern u8 D_00528180[];

extern f32   D_0047D7D0;          /* gp - 0x79A0 */
extern u8    D_004849B8;          /* gp - 0x7B8  */
extern u8    D_004849D8;          /* gp - 0x798  */

extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *p, u16 id);
extern void  func_291110(void *p, u16 id, s32 c, s32 d);

s32 normal_HelpMenuCloseState_522310(void *a, s32 b)
{
    if (b != 0) {
        func_290690(D_00528180, 0x2A, 0.0f, D_0047D7D0, -1.0f);
        func_290690(D_00528180, 0x29, 0.0f, D_0047D7D0, -1.0f);
        func_290690(D_00528180, 0x28, 0.0f, D_0047D7D0, -1.0f);
    }
    if (func_290770(D_00528180, 0x2A) <= 0.0f) {
        func_291110(D_00528180, 0x28, 0, 1);
        func_291110(D_00528180, 0x2A, 0, 1);
        func_291110(D_00528180, 0x29, 0, 1);
        D_004849B8 = 0;
        D_004849D8 = 0;
    }
    return 1;
}
