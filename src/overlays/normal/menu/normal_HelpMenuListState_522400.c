#include "types.h"
/* normal 0x00522400 -- the 0x7533 pane's per-frame scroll driver.  Five arms
 * off one state object: r==1 / r==2 report, then four flag-gated scroll
 * transitions (0x8000 close, 0x2000 open, bit0 snap-open, bit1 snap-shut).
 * Every `dsll32/dsra32 ..,16` here is a STORE-FORWARD: mwcc keeps the value
 * it just wrote to the s16 member in a register and re-narrows it instead of
 * reloading, so `p->f16 = X; if (p->f16 < 0)` is the right spelling and a
 * named s16 temp is NOT.
 * 0x40400000 is 3.0f and the product is left UNNAMED so it contracts to
 * adda.s/madd.s (see normal_FUN_004FD760's 0x25 slot). */

typedef struct St {
    u8  pad00[0xA];
    s16 f0A;
    u8  pad0C[2];
    s16 f0E;
    u8  pad10[2];
    s16 f12;
    u8  pad14[2];
    s16 f16;
} St;                                   /* >= 0x18 */

extern u8   D_005281C0[];
extern u8   D_00528180[];
extern s32  D_005281D4[3];      /* >8 B: keeps it OUT of small data
                                   (0x5281D4 is far outside the gp window,
                                   retail reads it lui %hi / lw %lo) */
extern u8   D_004B2570[];

extern s32  D_004849F0;           /* gp - 0x780  */
extern s32  D_004849A8;           /* gp - 0x7C8  */
extern s8   D_004849FC;           /* gp - 0x774  */
extern s16  D_004849F8;           /* gp - 0x778  */
extern f32  D_00484A04;           /* gp - 0x76C  */
extern f32  D_0047D7CC;           /* gp - 0x79A4 */

extern void  func_28EA90(void *ctx, s32 id, s32 a);
extern St   *func_28EC60(void *ctx);
extern void  func_290690(void *ctx, s32 id, f32 a, f32 b, f32 c);
extern s32   func_28E170(void *ctx, const u8 *p, s32 f, s32 a);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern s32   func_1839F0(const u8 *p, s32 a);
extern s32   func_183DD0(const u8 *p, s32 a);
extern void  func_28E9E0(void *ctx, s32 a);
extern void  func_290F60(void *ctx, s32 id, s32 c, s32 d);
extern void  normal_HelpMenuListCursorMoveCb_521b00(St *p, s32 a);
extern void  normal_HelpMenuListFill_522e30(s16 a);

s32 normal_HelpMenuListState_522400(void *unused, s32 init)
{
    St *p;
    s32 r;
    s32 sum;

    if (init != 0) {
        func_28EA90(D_005281C0, 0x7533, 0);
        p = func_28EC60(D_005281C0);
        p->f0E = D_004849F0 - 1;
        func_290690(D_00528180, 0x28, 1.0f, 0.1f, -1.0f);
    }
    r = func_28E170(D_005281C0, D_004B2570, 0, 0);
    p = func_28EC60(D_005281C0);
    if (r == 1) {
        sum = p->f12 + p->f16;
        D_004849FC = 0;
        D_004849F8 = sum;
        func_28EDE0(&D_004849A8, 0x753A, 1);
    } else if (r == 2) {
        func_28EDE0(&D_004849A8, 0x7539, 1);
    } else if (func_1839F0(D_004B2570, 0x8000) != 0) {
        if (p->f12 > 0 || p->f16 > 0) {
            func_28E9E0(D_005281C0, 0);
        }
        if (p->f16 > 0) {
            p->f16 = p->f16 - (s16)(p->f0A + 1);
            if (p->f16 < 0) {
                p->f16 = 0;
                p->f12 = 0;
            }
            normal_HelpMenuListFill_522e30(p->f16);
        } else {
            p->f16 = 0;
            p->f12 = 0;
        }
        if (p->f16 < 0) {
            p->f16 = 0;
        }
        normal_HelpMenuListCursorMoveCb_521b00(p, 0);
    } else if (func_1839F0(D_004B2570, 0x2000) != 0) {
        if (p->f12 < p->f0A || p->f16 < p->f0E - p->f0A) {
            func_28E9E0(D_005281C0, 0);
        }
        if (p->f16 < p->f0E - p->f0A) {
            p->f16 = p->f16 + (s16)(p->f0A + 1);
            if (p->f16 > p->f0E - p->f0A) {
                p->f12 = p->f0A;
                p->f16 = p->f0E - p->f0A;
            }
        } else {
            p->f12 = p->f0A;
            p->f16 = p->f0E - p->f0A;
        }
        if (p->f16 < 0) {
            p->f16 = 0;
        }
        normal_HelpMenuListCursorMoveCb_521b00(p, 0);
    } else if ((D_005281D4[0] & 1) && func_1839F0(D_004B2570, 0x1000) != 0
               && func_183DD0(D_004B2570, 0x1000) == 0) {
        if (p->f12 == 0 && p->f16 == 0 && p->f0E > 0) {
            func_28E9E0(D_005281C0, 0);
            p->f12 = p->f0A;
            p->f16 = p->f0E - p->f0A;
            func_290F60(D_00528180, 0x2B, 0x154,
                        (s32)(3.0f + (f32)p->f16 * D_00484A04));
            normal_HelpMenuListCursorMoveCb_521b00(p, 0);
            if (p->f16 < 0) {
                p->f16 = 0;
            }
        }
    } else if ((D_005281D4[0] & 2) && func_1839F0(D_004B2570, 0x4000) != 0
               && func_183DD0(D_004B2570, 0x4000) == 0) {
        if (p->f12 == p->f0A && p->f16 == p->f0E - p->f0A && p->f0E > 0) {
            func_28E9E0(D_005281C0, 0);
            p->f12 = 0;
            p->f16 = 0;
            func_290F60(D_00528180, 0x2B, 0x154,
                        (s32)(3.0f + (f32)p->f16 * D_00484A04));
            normal_HelpMenuListCursorMoveCb_521b00(p, 0);
            if (p->f16 < 0) {
                p->f16 = 0;
            }
        }
    }
    return 1;
}
