/* ag9a80 (session 33): CLOSED, byte-identical.  The $2/$3 exchange that
 * parked this at 14 for many sessions was mwcc's SCHEDULER, not the register
 * allocator: retail interleaves the `id = i + 9` addiu into the MIDDLE of the
 * `y = i * 0x26` shift/add chain (source-position-driven, like the vreg
 * creation order lever), and in the first loop-body call it ALSO defers the
 * `v = 0.02f*i; v = 0.35f-v;` float statements to AFTER that chain and the
 * call's integer argument setup instead of before it -- moving the float pair
 * down past the `t`/`id`/`y` computation closed the last 3-word argument-order
 * residue at 0x00509B6C.  Splitting `y = i * 0x26` into its own statements
 * with `id = i + 9` textually inserted between the *8+i step and the *2+i
 * step reproduces retail's mid-chain interleave for BOTH occurrences (the
 * loop body and the `k` tail), even though the two occurrences differ in
 * exactly where in the 5-op chain the interleave falls (after the first
 * shift for the `k` block, after the first add+shift for the loop body). */
#include "types.h"
/* normal 0x00509A80 -- the 0x7531 dialog's open, its two-row layout loop and
 * the answer poll.  Widget ids are u16 (`andi $5, $rX, 0xFFFF` at every call).
 * The `mul.s` / `sub.s` in the loop is NOT contracted, so the product is its
 * own statement ([[normal-madd-contraction]]).
 * m2c renders the last dispatch as an irregular `switch`; the listing is a
 * `beql`/`beql` compare CHAIN testing 1 before 0 -- but mwcc normalises the
 * order, so `case 0` must come FIRST in the source to get retail's dispatch.
 *
 * CLOSED (session 33/ag9a80): see the mechanism note above the #include. */

extern const u8 D_005264C0;
extern const u8 D_005264D0;
extern u8 D_004B2570[0x10];       /* main-image object; an ADDRESS, and the
                                     size keeps it out of small data */

/* the panel objects must be OVER the small-data threshold or every reference
 * comes out GPREL16 instead of retail's lui/%lo -- 20 words short. */
typedef struct Panel { u8 pad000[0x40]; } Panel;
extern Panel D_00527C40;
extern Panel D_00527C80;

typedef struct Rec {
    u8   pad000[0x12];
    s16  f012;
} Rec;

typedef struct Wid {
    u8   pad000[0x20];
    void *f020;
} Wid;

typedef struct Box {
    u8   pad000[4];
    s16  f004;
    s16  f006;
    u8   pad008[4];
    s16  f00C;
    s16  f00E;
} Box;

extern s16   D_00484600;          /* gp - 0xB70 */
extern s16   D_00484604;          /* gp - 0xB6C */
extern s16   D_004845B8;          /* gp - 0xBB8 */

extern s32  func_1FEDE0(void);
extern void func_27C2A0(s32 a, const u8 *p);
extern void func_288130(s32 a);
extern s32  func_28E170(Panel *p, void *q, s32 c, s32 d);
extern void func_28EA90(Panel *p, s32 id, s32 a);
extern Rec *func_28EC60(Panel *p);
extern void func_28EDE0(void *p, s32 id, s32 a);
extern void func_290010(Panel *p, s32 id, s32 c, s32 d);
extern Wid *func_290460(Panel *p, u16 id);
extern void func_2905B0(Panel *p, s32 id, f32 r, f32 g, f32 b, f32 a);
extern void func_290690(Panel *p, s32 id, f32 x, f32 y, f32 z);
extern void func_2907A0(Panel *p, s32 id, f32 x);
extern void func_290F50(Panel *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void func_290F60(Panel *p, s32 id, s32 c, s32 d);
extern void func_291110(Panel *p, u16 id, s32 c, s32 d);
extern s32  func_3E7E10(s32 a);
extern void normal_ShopMenuTopPickAnimStep_509e90(void);
extern void normal_ShopMenuMoneyRefresh_50ac80(s32 a, s32 c);

s32 normal_ShopMenuTopState_509a80(void *a, s32 b)
{
    s32 i;
    s32 y;
    f32 v;
    Rec *w;
    s32 r;
    s16 k;
    Box *bx;
    s32 t;
    s32 id;

    if (b != 0) {
        func_288130(1);
        func_27C2A0(0, &D_005264C0);
        func_27C2A0(0, &D_005264D0);
        func_291110(&D_00527C40, 0x30, 1, 1);
        func_290F60(&D_00527C40, 0x30, 0x26, 0x6A);
        func_2907A0(&D_00527C40, 0x30, 0.0f);
        func_290690(&D_00527C40, 0x30, 1.0f, 0.05f, -1.0f);
        func_28EA90(&D_00527C80, 0x7531, 0);
        i = 0;
        do {
            /* product and difference in the SAME variable: written as two
             * variables mwcc contracts this into adda.s/msub.s and retail has
             * plain mul.s/sub.s.  15 other spellings measured, incl. volatile
             * and every operand order -- only reusing the destination works. */
            t = i * 8;
            id = i + 9;
            t = t + i;
            t = t * 2;
            t = t + i;
            y = t * 2;
            v = 0.02f * (f32)i;
            v = 0.35f - v;
            func_290F50(&D_00527C40, (u16)id, 0x21, y + 0x32, 0, v);
            func_290F50(&D_00527C40, (u16)(i + 6), 0x24, y + 0x35, 0, v);
            func_291110(&D_00527C40, (u16)(i + 0xB), 1, 1);
            i += 1;
        } while (i < 2);
        k = func_28EC60(&D_00527C80)->f012;
        t = k * 8;
        id = k + 9;
        t = t + k;
        t = t * 2;
        t = t + k;
        y = t * 2;
        func_290F50(&D_00527C40, (u16)id, 0x2B, y + 0x32, 0, 0.35f);
        func_290F50(&D_00527C40, (u16)(k + 6), 0x2E, y + 0x35, 0, 0.35f);
        D_00484600 = 0;
        normal_ShopMenuMoneyRefresh_50ac80(0x15, 0x14);
        func_291110(&D_00527C40, 0x11, 1, 1);
        func_291110(&D_00527C40, 0x10, 1, 1);
        func_290F50(&D_00527C40, 0x11, 0x104, 0x12, 0, 0.2f);
        func_290F50(&D_00527C40, 0x10, 0x107, 0x15, 0, 0.2f);
        func_2905B0(&D_00527C40, 0x10, 0.0f, 0.0f, 0.0f, 0.4f);
        func_290010(&D_00527C40, 0x1A, 0, -1);
    }
    if (D_00484600 == 0) {
        r = func_28E170(&D_00527C80, D_004B2570, 4, 0);
        w = func_28EC60(&D_00527C80);
        if (r == 1) {
            if ((func_3E7E10(func_1FEDE0()) == 0) && (w->f012 == 0)) {
                return 0;
            }
            D_00484600 = 1;
            func_2905B0(&D_00527C40, 0xE, 1.0f, 1.0f, 1.0f, 1.0f);
            func_290690(&D_00527C40, 0x30, 0.0f, -0.05f, -1.0f);
            D_00484604 = w->f012;
        } else if (r == 2) {
            func_28EDE0(&D_004845B8, 0x7533, 1);
        }
    }
    normal_ShopMenuTopPickAnimStep_509e90();
    if (D_00484600 == 7) {
        D_00484600 = 0;
        bx = func_290460(&D_00527C40, (u16)(D_00484604 + 9))->f020;
        bx->f004 = 0x70;
        bx->f006 = 0x1B;
        bx->f00E = 4;
        bx->f00C = 4;
        switch (D_00484604) {
        case 0:
            func_28EDE0(&D_004845B8, 0x7534, 1);
            break;
        case 1:
            func_28EDE0(&D_004845B8, 0x7542, 1);
            break;
        }
    }
    return 1;
}
