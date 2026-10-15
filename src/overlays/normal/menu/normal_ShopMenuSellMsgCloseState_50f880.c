#include "types.h"
/* normal 0x0050F880 -- the TAIL of the 0x70-widget phase-handler family
 * (normal_FUN_0050F960 / normal_FUN_0050CA10) with a single call in the guard.
 *
 * f(void *, s32): `$4` is never read, the guard is on `b`, and every path
 * returns 1.  The guarded call is one func_290690; note that against the seed
 * the float arguments are SWAPPED -- `mtc1 $0,$f12` is 0.0f in slot three and
 * `lui 0x3F80 -> BF80 / mtc1 $2,$f14` is -1.0f in slot five, with the gp
 * literal D_0047D3C8 (gp - 0x7DA8) in the middle.
 */

extern const u8 D_00527E70;

extern f32   D_0047D3C8;          /* gp - 0x7DA8 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */

extern void  func_28D820(const u8 *p, s32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

s32 normal_ShopMenuSellMsgCloseState_50f880(void *a, s32 b)
{
    if (b != 0) {
        func_290690(D_004845CC, 0x70, 0.0f, D_0047D3C8, -1.0f);
    }
    func_28D820(&D_00527E70, 0x3F);
    func_28EDE0(D_004845C4, 0x7547, 0);
    return 1;
}
