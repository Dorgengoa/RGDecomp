#include "types.h"
/* normal 0x005092E0 -- builds two 0xB0-byte text/number blocks in the frame
 * and hands five icon slots to the widget at 0x65.  `dsll32 24 / dsra32 24`
 * on the fourth parameter is an s8 PARAMETER being re-normalised at its test,
 * not an s8 local. */

typedef struct Blk {
    s32 f000;
    u8  pad004[0xC - 4];
    s32 f00C;
    u8  pad010[0xB0 - 0x10];
} Blk;

extern const u8 D_00527CF0[];
extern const u8 D_00527D10[];
extern void *D_004845F8;          /* gp - 0xB78 */
extern void *D_004845CC;          /* gp - 0xBA4 */

extern void  func_131B60(const void *a, s32 b, s32 c);
extern void  func_28AA00(Blk *a);
extern const void *func_28AA30(void *a, s32 id);
extern void  func_28A9A0(const void *a, const void *b, Blk *c, s32 d);
extern void  func_28F510(void *a, s32 id, const void *c, s32 d);

s32 normal_ShopMenuConfirmTextSet_5092e0(s32 a, s32 b, s32 c, s8 alt)
{
    Blk x;
    Blk y;
    s32 k;

    func_131B60(D_00527CF0, 0, 0x20);
    func_131B60(D_00527D10, 0, 0x20);
    func_28AA00(&x);
    x.f00C = a;
    x.f000 = b;
    func_28A9A0(D_00527CF0, func_28AA30(D_004845F8, 6), &x, 1);
    func_28F510(D_004845CC, 0x65, D_00527CF0, 0);
    func_28AA00(&y);
    y.f000 = c * b;
    func_28A9A0(D_00527D10, func_28AA30(D_004845F8, 7), &y, 1);
    func_28F510(D_004845CC, 0x65, D_00527D10, 1);
    /* Retail's `bnel` branches AWAY carrying the 9 and falls through into
     * the 8, so the `if` arm is the ZERO case. */
    if (alt == 0) {
        k = 8;
    } else {
        k = 9;
    }
    func_28F510(D_004845CC, 0x65, func_28AA30(D_004845F8, k), 2);
    func_28F510(D_004845CC, 0x65, func_28AA30(D_004845F8, 0xA), 3);
    func_28F510(D_004845CC, 0x65, func_28AA30(D_004845F8, 0xB), 4);
    return 1;
}
