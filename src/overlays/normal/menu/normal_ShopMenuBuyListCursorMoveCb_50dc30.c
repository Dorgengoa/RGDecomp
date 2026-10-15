#include "types.h"
/* normal 0x0050DC30 -- the row-change handler: re-posts the caret, and when
 * the remembered row has moved, re-runs the slide and the row hook.  The table
 * lookup is `D_00527D30[f12 + f16]` and a NULL entry aborts with 0. */
typedef struct Row { u8 pad00[2]; s16 f02; u8 pad04[2]; s16 f06; u8 pad08[0x12 - 8]; s16 f12; s16 f14; s16 f16; } Row;

extern s32 D_00527D30[];

extern f32   D_0047D240;              /* gp - 0x7F30 */
extern f32   D_0047D34C;              /* gp - 0x7E24 */
extern void *D_004845C8;              /* gp - 0xBA8  */
extern f32   D_00484634;              /* gp - 0xB3C  */
extern s16   D_00484638;              /* gp - 0xB38  */
extern s32   D_0048464C;              /* gp - 0xB24  */

extern void func_28FC90(void *p, s32 id, s32 v, s32 n);
extern void func_290F50(void *p, u16 id, s32 a, s32 b, s32 c, f32 x);
extern void normal_ShopMenuBuyRowsRefresh_50b5c0(s32 a);
extern s32  normal_ShopMenuRowInfoShow_509460(void *h, f32 x, s32 b, s32 c, s32 d, s32 e);
extern void normal_ShopMenuBuyRowHintShow_50c550(s32 a);

s32 normal_ShopMenuBuyListCursorMoveCb_50dc30(Row *r)
{
    void *e;

    func_28FC90(D_004845C8, 0x1C, r->f02 + r->f12 * r->f06, 0);
    if (D_00484638 == r->f12) {
        func_290F50(D_004845C8, 0x25, 0, (s32)((f32)r->f16 * D_00484634), 0, D_0047D34C);
        normal_ShopMenuBuyRowsRefresh_50b5c0(r->f16);
    }
    e = (void *)D_00527D30[r->f12 + r->f16];
    if (e == NULL) {
        return 0;
    }
    normal_ShopMenuRowInfoShow_509460(e, D_0047D240, 0x34, 0x33, 0x56, 0x15E);
    D_00484638 = r->f12;
    D_0048464C = 0;
    normal_ShopMenuBuyRowHintShow_50c550(0);
    return 1;
}
