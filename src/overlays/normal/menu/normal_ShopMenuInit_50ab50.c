#include "types.h"
/* normal 0x0050AB50 -- the sibling of normal_ThinkMenuInit_5212b0: a 73-instruction,
 * ZERO-conditional-branch scene builder, 20 calls.  Same conventions: every
 * store written before a call fills that call's delay slot, allocator results
 * that are used immediately are locals, and everything read after an
 * intervening call is re-read from its global.
 * ⚠ `func_2A5920`'s prototype puts its two float parameters BEFORE the two
 * trailing integers.  Same registers either way -- the EABI numbers float and
 * integer arguments independently -- but the declaration order reaches the
 * SCHEDULE, and with the integers first mwcc fills the `mtc1`'s hazard slot
 * with `addiu $7,$0,1` and the unit is one word short.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern void *D_004845A8;
extern void *D_004845AC;
extern void *D_004845B0;
extern s16   D_004845B8;
extern void *D_004845C4;
extern void *D_004845C8;
extern void *D_004845CC;
extern void *D_004845D0;
extern void *D_004845D4;
extern u8    D_004845D8;
extern u8    D_004845DC;
extern s16   D_004845E0;
extern s16   D_004845E4;
extern void *D_004845FC;
extern s16   D_00480638;

extern const u8  D_00527C40;
extern const u8  D_00527C60;
extern const u8  D_00527C80;
extern const s32 D_004659E8;

extern void *func_207DF0(void);
extern void *func_206A60(void);
extern void *func_206A50(void);
extern void  func_14D830(void *p);
extern void  normal_ShopMenuClutBufAlloc_50b120(void);
extern void *func_15DE40(void);
extern void  func_158AC0(void *p, s32 id);
extern void  normal_ShopMenuResRequest_50b020(void);
extern void *func_1FEDF0(void);
extern void  func_3F0960(void *p, s32 n);
extern void  normal_ShopMenuResPoll_50ae40(void);
extern void *func_14E230(s32 id, void *h);
extern void  func_2A5920(void *p, s32 n, f32 x, f32 y, s32 a, s32 b);
extern void  func_2A5900(void *a, const u8 *b, const u8 *c, s16 *d, void *e);

void normal_ShopMenuInit_50ab50(void)
{
    void *h;

    D_004845A8 = func_207DF0();
    D_004845E4 = 0;
    h = func_206A60();
    D_004845AC = h;
    func_14D830(h);
    h = func_206A50();
    D_004845B0 = h;
    func_14D830(h);
    normal_ShopMenuClutBufAlloc_50b120();
    D_004845DC = 0;
    D_004845E0 = 1;
    D_004845D8 = 1;
    D_00480638 = 1;
    func_158AC0(func_15DE40(), 0x32D);
    D_004845FC = 0;
    normal_ShopMenuResRequest_50b020();
    func_3F0960(func_1FEDF0(), 8);
    normal_ShopMenuResPoll_50ae40();
    h = func_14E230(0x1B4, D_004845AC);
    D_004845D4 = h;
    func_2A5920(h, (s8)(D_004659E8 + 1), 0.0f, 0.0f, 0, 1);
    func_2A5900(D_004845D4, &D_00527C40, &D_00527C80, &D_004845B8, D_004845AC);
    D_004845C4 = &D_004845B8;
    D_004845C8 = (void *)&D_00527C40;
    D_004845D0 = (void *)&D_00527C80;
    D_004845CC = (void *)&D_00527C60;
}
