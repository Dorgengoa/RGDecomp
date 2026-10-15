#include "types.h"
/* normal 0x0050FED0 -- confirm handler: bumps or resets the row, resolves the
 * page record, runs the six-argument probe and only then commits.  The
 * func_291250's fourth argument here is o->f10, s32 (not the s64 value slot
 * the 0x0050BB00 site uses) -- the dead `lh $7` in the bnel delay slot is it. */
typedef struct Obj  { u8 pad00[0x10]; s16 f10; } Obj;
typedef struct Page { u8 pad00[0x14]; s16 f14; s16 f16; } Page;
typedef struct Cfg  { u8 pad00[0x11]; s8 f11; } Cfg;
typedef struct Sys  { u8 pad00[0x18]; void *f18; } Sys;

extern void *D_004845CC;              /* gp - 0xBA4 */
extern void *D_004845D0;              /* gp - 0xBA0 */
extern Cfg  *D_004845D4;              /* gp - 0xB9C */
extern void *D_0048467C;              /* gp - 0xAF4 */

extern void  func_289EF0(s32 a);
extern Page *func_28EA40(void *w, s32 id);
extern Sys  *func_1FEDE0(void);
extern s32   func_3C86E0(void *a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void  func_291250(void *w, u16 id, s32 slot, s32 v);
extern s32   func_3D4320(void *p);
extern s32   normal_ShopMenuSellTotalPriceSet_50ec80(s32 a, s32 b);

s32 normal_ShopMenuSellQtyCursorMoveCb_50fed0(Obj *o)
{
    Page *pg;

    if (o->f10 <= 0) {
        o->f10 = 1;
    } else {
        func_289EF0(4);
    }
    pg = func_28EA40(D_004845D0, 0x7534);
    if (func_3C86E0(func_1FEDE0()->f18, 0, D_004845D4->f11, pg->f14, pg->f16, 0) == 0) {
        return 0;
    }
    func_291250(D_004845CC, 0x4F, 0, o->f10);
    normal_ShopMenuSellTotalPriceSet_50ec80(func_3D4320(D_0048467C), o->f10);
    return 1;
}
