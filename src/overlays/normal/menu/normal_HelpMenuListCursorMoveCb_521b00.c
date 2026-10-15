#include "types.h"
/* normal 0x00521B00 -- the 0x2A widget bring-up: bail if the open fails, run
 * the eight-slot init pair, then the three per-selection calls.  The final
 * `3.0f + (f32)f16 * D_00484A04` is left INLINE so the scheduler keeps the
 * adda.s/madd.s contraction retail has -- naming the product would kill it. */

typedef struct Box {
    u8  pad00[0x12];
    s16 f12;
    u8  pad14[0x16 - 0x14];
    s16 f16;
} Box;

extern const u8 D_00528180[];

extern f32 D_00484A04;            /* gp - 0x76C */

extern s32  func_290460(const u8 *w, s32 id);
extern void func_28FBF0(const u8 *w, s32 id, s32 a, s32 i);
extern void func_28F850(const u8 *w, s32 id, s32 a, s32 i);
extern void func_290F60(const u8 *w, s32 id, s32 a, s32 b);
extern void normal_HelpMenuListFill_522e30(s32 a);
extern void func_290F50(const u8 *w, u16 id, s32 x, s32 y, s32 z, f32 t);

s32 normal_HelpMenuListCursorMoveCb_521b00(Box *p)
{
    s32 i;

    if (func_290460(D_00528180, 0x2A) == 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        func_28FBF0(D_00528180, 0x2A, 0x14F, i);
        func_28F850(D_00528180, 0x2A, 4, i);
    }
    func_28FBF0(D_00528180, 0x2A, 0, p->f12);
    func_28F850(D_00528180, 0x2A, 0, p->f12);
    func_290F60(D_00528180, 0x29, 0x52, p->f12 * 27 + 0x70);
    normal_HelpMenuListFill_522e30(p->f16);
    func_290F50(D_00528180, 0x2B, 0x154,
                (s32)(3.0f + (f32)p->f16 * D_00484A04), 0, 0.25f);
    return 1;
}
