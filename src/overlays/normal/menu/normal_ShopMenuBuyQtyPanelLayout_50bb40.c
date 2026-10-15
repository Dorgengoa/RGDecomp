#include "types.h"
/* normal 0x0050BB40 -- builds the 0x4A/0x4D/0x77-0x7A/0x4F item panel for one
 * entry and returns the mode func_3CE860 reported.
 * # m2c emits `func_291110()` with no arguments in the else arm; the two arms
 * differ only in ONE argument and $7 is materialised before the branch.
 * The `dsll32 $2,$rX,0 / dsra32 $2,$2,0` pairs are s32 -> s64 widening into
 * the two `sd` fields, so 3CE860 and 3CE6E0 return s32 and the fields are s64. */

extern void *D_004845CC;          /* gp - 0xBA4 */
extern void *D_004845F8;          /* gp - 0xB78 */

typedef struct Item {
    u8   pad000[0x48];
    s64  f048;
    u8   pad050[0x68 - 0x50];
    s64  f068;
    u8   pad070[0x76 - 0x70];
    s16  f076;
    s16  f078;
} Item;

extern void  func_288E50(s32 w, s32 a, s32 b, s32 c);
extern void  func_28A800(s32 w, s32 a, s32 b, s32 c, s32 d);
extern s32   func_28AA30(void *p, s32 a);
extern Item *func_28F2B0(void *p, s32 id, s32 a);
extern void  func_28F300(void *p, s32 id, s32 a, s32 b);
extern s32   func_28F400(void *p, s32 id, s32 a);
extern void  func_28F510(void *p, s32 id, s32 a, s32 b);
extern void  func_28F590(void *p, s32 id, s32 a, s32 b);
extern void  func_28F670(void *p, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern s32   func_28FE10(void *p, s32 id, s32 a);
extern void  func_290F60(void *p, s32 id, s32 c, s32 d);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern s32   func_3CE6E0(s32 a);
extern s32   func_3CE860(void);
extern s32   func_3CE890(s32 a);
extern s32   func_3CE930(s32 a);
extern void  normal_ShopMenuBuyTotalPriceSet_50bb00(s32 a, s32 b);

s32 normal_ShopMenuBuyQtyPanelLayout_50bb40(s32 arg)
{
    s32 mode;
    s32 w;
    s32 v;
    Item *it;

    if (arg == 0) {
        return 0;
    }
    mode = func_3CE860();
    w = func_28FE10(D_004845CC, 0x4C, 0);
    if (w == 0) {
        return 0;
    }
    func_288E50(w, func_3CE890(arg), 0x28, 0x2D);
    func_28F510(D_004845CC, 0x4A, func_28AA30(D_004845F8, 3), 0);
    if (mode == 1) {
        func_291110(D_004845CC, 0x4D, 0, 1);
    } else {
        func_291110(D_004845CC, 0x4D, 1, 1);
    }
    func_28F590(D_004845CC, 0x4A, 0xA0 - func_28F400(D_004845CC, 0x4A, 0) / 2, 0);
    func_28F510(D_004845CC, 0x4A, func_3CE930(arg), 1);
    func_28F300(D_004845CC, 0x4A, 0xA8, 1);
    w = func_28FE10(D_004845CC, 0x7A, 0);
    if (w == 0) {
        return 0;
    }
    func_291110(D_004845CC, 0x77, 1, 1);
    func_291110(D_004845CC, 0x78, 1, 1);
    func_291110(D_004845CC, 0x79, 1, 1);
    func_291110(D_004845CC, 0x7A, 1, 1);
    func_28A800(w, func_28AA30(D_004845F8, 0x14), 0, 0, -2);
    func_290F60(D_004845CC, 0x77, 0x70, 0x5A);
    func_290F60(D_004845CC, 0x78, 0x3E, 0x72);
    func_290F60(D_004845CC, 0x79, 0xB4, 0x44);
    func_290F60(D_004845CC, 0x7A, 0x3E, 0x44);
    it = func_28F2B0(D_004845CC, 0x4F, 0);
    if (it == 0) {
        return 0;
    }
    v = func_3CE6E0(arg);
    if (mode == 0x64) {
        it->f078 = 0;
        it->f076 = 0;
        func_28F670(D_004845CC, 0x4F, 0x1A, 0x10, 0x1A, 0x10, 0);
    } else {
        it->f076 = 0xC;
        it->f078 = 0x10;
        it->f068 = mode;
        func_28F670(D_004845CC, 0x4F, 0, 0, 0, 0, 0);
    }
    it->f048 = v;
    normal_ShopMenuBuyTotalPriceSet_50bb00(v, 1);
    return mode;
}
