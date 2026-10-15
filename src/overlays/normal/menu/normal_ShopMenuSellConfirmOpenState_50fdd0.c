#include "types.h"
/* normal 0x0050FDD0 -- the 0x63/0x65/0x66 dialogue-open handler.  Twin of
 * normal_FUN_0050CE50: same func_291110 / func_290F60 / func_290690 /
 * normal_ShopMenuYesNoHighlight_509270 spine on the gp handle D_004845CC, differing in the
 * record it reads, the flag it writes and two message ids.
 */

typedef struct Hdl { u8 pad00[0x14]; s16 f14; } Hdl;
typedef struct Rec { u8 pad00[0x10]; s16 *f10; } Rec;

extern u8 D_00527E70[];

extern f32   D_0047D460;          /* gp - 0x7D10 */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */
extern Rec  *D_0048467C;          /* gp - 0xAF4  */
extern u8    D_00484684;          /* gp - 0xAEC  */

extern void  normal_ShopMenuYesNoHighlight_509270(s32 a, void *p, s32 c);
extern void  normal_ShopMenuConfirmTextSet_5092e0(s32 a, s32 b, s32 c, s32 d);
extern void  func_28D820(void *p, s32 id);
extern Hdl  *func_28EA40(void *p, s32 id);
extern void  func_28EA90(void *p, s32 id, s32 a);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern s32   func_3D4320(Rec *p);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F60(void *p, u16 id, s32 c, s32 d);
extern void  func_291110(void *p, u16 id, s32 c, s32 d);

s32 normal_ShopMenuSellConfirmOpenState_50fdd0(void *a, s32 b)
{
    Hdl *h;
    Rec *r;
    s32  v;

    if (b != 0) {
        h = func_28EA40(D_004845D0, 0x7535);
        r = D_0048467C;
        v = *r->f10;
        normal_ShopMenuConfirmTextSet_5092e0(v, h->f14, func_3D4320(r), 1);
        func_291110(D_004845CC, 0x63, 1, 1);
        func_290F60(D_004845CC, 0x63, 0x8C, 0x72);
        func_290690(D_004845CC, 0x63, 1.0f, D_0047D460, 0.0f);
        D_00484684 = 1;
        normal_ShopMenuYesNoHighlight_509270(1, D_004845CC, 0x65);
        func_290F60(D_004845CC, 0x66, 0x7C, 0x58);
        func_28EA90(D_004845D0, 0x7536, 0);
    }
    func_28D820(D_00527E70, 0x3F);
    func_28EDE0(D_004845C4, 0x7549, 0);
    return 1;
}
