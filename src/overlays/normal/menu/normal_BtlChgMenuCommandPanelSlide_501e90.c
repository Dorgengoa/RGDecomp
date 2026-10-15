#include "types.h"
/* normal 0x00501E90 -- the two-sided 0x2B panel placer.  `base` is
 * normal_FUN_00505F90's slot times 125 (`sll 5 / subu / sll 2 / addu`) plus
 * 0x73.  The two arms differ ONLY in which of func_290F60 / func_290F50 gets
 * `base` and which gets `base + 0x64`, and in the func_290690 float triple
 * (1.0f,K,0.0f vs 0.0f,K,1.0f).  Three out-params at sp+0x4C / 0x48 / 0x44:
 * locals go top-down in DECLARATION order.  No value is returned. */

extern void *D_00484454;          /* gp - 0xD1C  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern f32   D_0047D278;          /* gp - 0x7EF8 */
extern f32   D_0047D518;          /* gp - 0x7C58 */

extern void func_289A40(void *p, s32 *a, s32 *b, s32 *c);
extern s32  normal_BtlChgPageGetMember_505f90(void *p);
extern void func_290F60(void *w, u16 id, s32 a, s32 b);
extern void func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 f);
extern void func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

void normal_BtlChgMenuCommandPanelSlide_501e90(s32 a, s32 b)
{
    s32 p;
    s32 q;
    s32 r;
    s32 base;

    func_289A40(D_00484454, &p, &q, &r);
    base = normal_BtlChgPageGetMember_505f90(D_00484454) * 125 + 0x73;
    if (a != 0) {
        if (b != 0) {
            func_290F60(D_0048449C, 0x2B, base + 0x64, 0xDB);
        }
        func_290F50(D_0048449C, 0x2B, base, 0xDB, 0, D_0047D278);
        func_290690(D_0048449C, 0x2C, 1.0f, D_0047D518, 0.0f);
        func_290690(D_0048449C, 0x2D, 1.0f, D_0047D518, 0.0f);
        func_290690(D_0048449C, 0x51, 1.0f, D_0047D518, 0.0f);
        func_290690(D_0048449C, 0x52, 1.0f, D_0047D518, 0.0f);
        func_290690(D_0048449C, 0x53, 1.0f, D_0047D518, 0.0f);
        func_290690(D_0048449C, 0x54, 1.0f, D_0047D518, 0.0f);
    } else {
        if (b != 0) {
            func_290F60(D_0048449C, 0x2B, base, 0xDB);
        }
        func_290F50(D_0048449C, 0x2B, base + 0x64, 0xDB, 0, D_0047D278);
        func_290690(D_0048449C, 0x2C, 0.0f, D_0047D518, 1.0f);
        func_290690(D_0048449C, 0x2D, 0.0f, D_0047D518, 1.0f);
        func_290690(D_0048449C, 0x51, 0.0f, D_0047D518, 1.0f);
        func_290690(D_0048449C, 0x52, 0.0f, D_0047D518, 1.0f);
        func_290690(D_0048449C, 0x53, 0.0f, D_0047D518, 1.0f);
        func_290690(D_0048449C, 0x54, 0.0f, D_0047D518, 1.0f);
    }
}
