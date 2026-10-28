/* rgp:protos */
#define RGP_SELF_normal_ShopMenuConfirmTextSet_5092e0 1
#include "port/game_protos.h"
#line 1
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

extern u8 normal_D_00527CF0[];
extern u8 normal_D_00527D10[];
extern void *D_004845F8;          /* gp - 0xB78 */
extern void *D_004845CC;          /* gp - 0xBA4 */

extern void  memset(const void *a, s32 b, s32 c);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuConfirmTextSet_5092e0(s32 a, s32 b, s32 c, s8 alt)
{
    Blk x __attribute__((aligned(16)));
    Blk y __attribute__((aligned(16)));
    s32 k;

    memset(normal_D_00527CF0, 0, 0x20);
    memset(normal_D_00527D10, 0, 0x20);
    MsgFormatParamsCtor_28aa00(&x);
    x.f00C = a;
    x.f000 = b;
    MsgFormat_28a9a0(normal_D_00527CF0, MsgTableLookup_28aa30(D_004845F8, 6), &x, 1);
    UiSetTextString_28f510(D_004845CC, 0x65, normal_D_00527CF0, 0);
    MsgFormatParamsCtor_28aa00(&y);
    y.f000 = c * b;
    MsgFormat_28a9a0(normal_D_00527D10, MsgTableLookup_28aa30(D_004845F8, 7), &y, 1);
    UiSetTextString_28f510(D_004845CC, 0x65, normal_D_00527D10, 1);
    /* Retail's `bnel` branches AWAY carrying the 9 and falls through into
     * the 8, so the `if` arm is the ZERO case. */
    if (alt == 0) {
        k = 8;
    } else {
        k = 9;
    }
    UiSetTextString_28f510(D_004845CC, 0x65, MsgTableLookup_28aa30(D_004845F8, k), 2);
    UiSetTextString_28f510(D_004845CC, 0x65, MsgTableLookup_28aa30(D_004845F8, 0xA), 3);
    UiSetTextString_28f510(D_004845CC, 0x65, MsgTableLookup_28aa30(D_004845F8, 0xB), 4);
    return 1;
}
