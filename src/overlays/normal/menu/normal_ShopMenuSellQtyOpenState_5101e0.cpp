#include "types.h"
/* normal 0x005101E0 -- the field menu's page-in for the 0x48 frame.  `b != 0`
 * arms the frame and the five 0x40/0x33/0x5B/0x57 sliders, then branches on
 * whether the party object has a mount (func_3D46C0): with one, the 0x67
 * rider widgets are laid out, without one the 0x57 anchor is moved instead.
 * Both paths run the two normal_FUN_0050e* helpers and the count query.
 *
 * `$4` is never read -- the f(void *, s32) state-handler family; the guard is
 * on `b` and both paths return 1.
 * `lw $25,0x0($4) / lw $25,0x50($25) / jalr $25` is a REAL C++ virtual, so
 * this unit is .cpp: a struct of function pointers gives `jalr $v0`.  mwcc
 * puts the first virtual at vtable +0x08, so 0x50 is index (0x50-8)/4 = 18;
 * the placeholder list is expanded from that OFFSET so the index cannot drift.
 * `sh $3, 0x14($2)` sits in the `blez`'s DELAY SLOT: `p->f14 = 1;` is the
 * statement BEFORE the if, not part of either arm.
 * `daddu $16,$2,$0` is in func_28EA40's DELAY SLOT and captures the VIRTUAL
 * call's result. */

struct Party {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual s32 count();          /* slot 18 -> vtable +0x50 */
};

typedef struct Panel { u8 pad00[0xC]; s16 f0C; u8 pad0E[6]; s16 f14; } Panel;

extern "C" {

extern void  *D_004845C4;         /* gp - 0xBAC */
extern void  *D_004845C8;         /* gp - 0xBA8 */
extern void  *D_004845CC;         /* gp - 0xBA4 */
extern void  *D_004845D0;         /* gp - 0xBA0 */
extern void  *D_004845D4;         /* gp - 0xB9C */
extern f32    D_0047D460;         /* gp - 0x7D10 */
extern f32    D_0047D4AC;         /* gp - 0x7CC4 */
extern f32    D_0047D49C;         /* gp - 0x7CD4 */

extern void  func_291110(void *a, u16 b, s32 c, s32 d);
extern void  func_28EA90(void *a, s32 b, s32 c);
extern void  func_290F60(void *a, u16 b, s32 c, s32 d);
extern void  func_290690(void *a, u16 b, f32 c, f32 d, f32 e);
extern s32   func_3D46C0(Party *a);
extern void  func_290010(void *a, u16 b, s32 c, s32 d);
extern void  func_2A0600(void *a, void *b, Party *c, s32 d, s32 e, s32 f, s32 g);
extern void  normal_ShopMenuSellItemStatusLayout_50ef80(Party *a);
extern void  normal_ShopMenuSellQtyPanelLayout_50ecc0(Party *a);
extern Panel *func_28EA40(void *a, s32 b);
extern void  func_28EDE0(void *a, s32 b, s32 c);

}

extern Party *D_0048467C;         /* gp - 0xAF4 */

extern "C" s32 normal_ShopMenuSellQtyOpenState_5101e0(void *a, s32 b)
{
    s32    n;
    Panel *p;

    if (b != 0) {
        func_291110(D_004845CC, 0x48, 1, 1);
        func_28EA90(D_004845D0, 0x7535, 0);
        func_291110(D_004845CC, 0x48, 1, 1);
        func_290F60(D_004845CC, 0x48, 0x7A, 0x6A);
        func_290690(D_004845CC, 0x48, 1.0f, D_0047D460, 0.0f);
        func_290690(D_004845C8, 0x40, 0.0f, D_0047D4AC, -1.0f);
        func_290690(D_004845C8, 0x33, 0.0f, D_0047D49C, -1.0f);
        func_290690(D_004845CC, 0x5B, 0.0f, D_0047D4AC, -1.0f);
        func_290690(D_004845CC, 0x57, 1.0f, D_0047D460, 0.0f);
        if (func_3D46C0(D_0048467C) != 0) {
            func_290010(D_004845CC, 0x67, 1, -1);
            func_2A0600(D_004845D4, D_004845CC, D_0048467C, 0x6F, 0x6C, 0x68, 0x6E);
            func_290690(D_004845CC, 0x67, 1.0f, D_0047D460, -1.0f);
            func_290F60(D_004845CC, 0x57, 0x3C, 0x100);
            func_290F60(D_004845CC, 0x67, 0xF9, 0x100);
        } else {
            func_290F60(D_004845CC, 0x57, 0xB6, 0x100);
        }
        normal_ShopMenuSellItemStatusLayout_50ef80(D_0048467C);
        normal_ShopMenuSellQtyPanelLayout_50ecc0(D_0048467C);
        n = D_0048467C->count();
        p = func_28EA40(D_004845D0, 0x7535);
        p->f14 = 1;
        if (n > 0) {
            p->f0C = n;
        } else {
            p->f0C = 0x63;
        }
    }
    func_28EDE0(D_004845C4, 0x7546, 0);
    return 1;
}
