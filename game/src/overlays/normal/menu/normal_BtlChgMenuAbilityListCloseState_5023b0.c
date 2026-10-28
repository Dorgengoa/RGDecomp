/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuAbilityListCloseState_5023b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005023B0 -- the 0x01 / 0x40 / 0x1E widget phase handler on the gp
 * handle D_0048449C (f(void *, s32), `$4` never read, guard on `b`, returns 1).
 *
 * `lui 0x3E00 / mtc1 $2,$f13` is the literal 0.125f and `lui 0x3F80` the
 * literal 1.0f -- both inline, only the func_290F50 scale comes from gp.
 * The tail runs on EVERY call: the 0x456 byte of the D_00484454 record is
 * cleared BEFORE the func_00505FB0 poll (its gp load sits in the store's
 * following delay slot -- a gp load will not move above a store).
 * `beql $2,$0` PAST the block is a plain `!= 0` guard.
 */

typedef struct Obj { u8 pad000[0x456]; u8 f456; } Obj;

extern f32   D_0047D278;          /* gp - 0x7EF8 */
extern Obj  *D_00484454;          /* gp - 0xD1C  */
extern void *D_0048449C;          /* gp - 0xCD4  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuAbilityListCloseState_5023b0(void *a, s32 b)
{
    if (b != 0) {
        UiMoveWidgetUniform_290f50(D_0048449C, 1, 0x15E, 0x147, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(D_0048449C, 1, 0.0f, 0.125f, 1.0f);
        UiMoveWidgetUniform_290f50(D_0048449C, 0x40, 0x15E, 0x147, D_0047D278, 0);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x1E, 0.0f, 0.125f, 1.0f);
    }
    normal_BtlChgPageStop_505fd0(D_00484454);
    normal_BtlChgMenuCursorShow_503730(0);
    D_00484454->f456 = 0;
    if (((signed char)normal_BtlChgPageGetCloseCode_505fb0(D_00484454)) != 0) {
        normal_BtlChgMenuPanelGlowMaybe_4faf20(-1, 1);
        normal_BtlChgPageSetCloseCode_505fc0(D_00484454, 2);
    }
    return 1;
}
