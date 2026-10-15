#include "types.h"
/* normal 0x0051D570 -- 0x791B-widget phase handler, same 0x34-Layout family as
 * normal_FUN_0050F960 / normal_FUN_0051E5F0.  Frame -0x60: sq $16 at 0x00 and
 * sd $31 at 0x10 are the whole save area (0x00-0x1F), Layout at sp+0x20, so
 * there is NO extra stack object.
 *
 * f(void *, s32), `$4` never read, guard on `b`.  The two leading func_290690
 * calls take the ARGUMENT SWAP form: `mtc1 $0,$f12` / `lui 0xBF800000,$f14`
 * is (0.0f, D_0047D9B8, -1.0f), the mirror of the seed's (1.0f, K, 0.0f).
 * `sh $2` then `dsll32/dsra32 ..,16` is the s16 global D_00480784 written from
 * an s32 return and immediately re-tested -- store forwarding, not a reload.
 * The tail `c.le.s $f0,$f1` with `bc1tl` PAST the call is a source `>`.
 */

typedef struct Layout {
    void *f00;
    s32   f04;
    u8    pad08[8];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    s32   f2C;
    s16   f30;
} Layout;

typedef struct Ctx {
    u8    pad00[0x10];
    void *f10;
} Ctx;

extern f32   D_0047D470;          /* gp - 0x7D00 */
extern f32   D_0047D998;          /* gp - 0x77D8 */
extern f32   D_0047D9B8;          /* gp - 0x77B8 */
extern s16   D_0048075C;          /* gp - 0x4A14 */
extern s16   D_00480784;          /* gp - 0x49EC */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_00484718;          /* gp - 0xA58  */
extern void *D_00484720;          /* gp - 0xA50  */
extern void *D_00484770;          /* gp - 0xA00  */
extern s16   D_004848F0;          /* gp - 0x880  */

extern void  func_131B60(void *p, s32 v, s32 n);
extern Ctx  *func_1FEDE0(void);
extern void  func_289EF0(s32 a);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_28F510(void *w, u16 id, void *p, s32 n);
extern s32   func_28F620(void *w, u16 id, s32 n);
extern void *func_28FE10(void *w, u16 id, s32 n);
extern void  func_290010(void *w, u16 id, s32 a, s32 b);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *w, u16 id);
extern void  func_290F60(void *w, u16 id, s32 x, s32 y);
extern void  func_3CC9C0(void *p, s32 a, s32 b, s32 c);

extern void  normal_TransHunterRewardMsgFormat_51d150(s32 a, s32 b);
extern s32   normal_TransHunterRewardFindNext_51d320(void);

s32 normal_TransHunterRewardOpenState_51d570(void *a, s32 b)
{
    Layout lay;
    Ctx *c;

    if (b != 0) {
        func_290690(D_00484710, 0x7642, 0.0f, D_0047D9B8, -1.0f);
        func_290690(D_00484710, 0x764A, 0.0f, D_0047D9B8, -1.0f);
        func_28EA90(D_00484720, 0xF, 0);
        c = func_1FEDE0();
        if (D_004848F0 == 0) {
            D_00480784 = normal_TransHunterRewardFindNext_51d320();
            if (D_00480784 == 0) {
                func_3CC9C0(c->f10, 0xF, D_0048075C, 0);
                func_28EDE0(D_0048470C, 0x1E, 0);
                return 1;
            }
        }
        normal_TransHunterRewardMsgFormat_51d150(D_00480784, D_004848F0 != 0);
        func_290010(D_00484718, 0x791B, 1, -1);
        func_290690(D_00484718, 0x791B, 1.0f, D_0047D998, 0.0f);
        func_28F510(D_00484718, 0x791B, func_28AA30(D_00484770, 6), 0);

        func_131B60(&lay, 0, 0x34);
        lay.f00 = func_28FE10(D_00484718, 0x791B, 0);
        lay.f04 = func_28F620(D_00484718, 0x791B, 0);
        lay.f10 = 0x9C;
        lay.f14 = 0x6E;
        lay.f18 = 0x4E;
        lay.f1C = 8;
        lay.f20 = 0x4B;
        lay.f24 = 0x49;
        lay.f28 = 0x199;
        lay.f2C = 0x12A;
        lay.f30 = 4;
        func_28D0C0(&lay, 0, 0, 0);

        func_290F60(D_00484718, 0x791C, 0x87, 0x98);
        func_289EF0(0x20);
    }
    if (func_290770(D_00484710, 0x791B) > D_0047D470) {
        func_28EDE0(D_0048470C, 0x1D, 0);
    }
    return 1;
}
