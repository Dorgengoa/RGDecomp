#include "types.h"
/* normal 0x0050A6F0 -- the shop/list panel's three-object build (0x27C40,
 * 0x27C60, 0x27C80), the 8 x 0x20 palette blit, then the phase-2 poll.
 * # m2c gives func_42C950 SIX arguments; the last four are the LEFTOVER
 * registers of the bitfield store above it -- the call takes two.
 * # func_15DE40 takes NO argument; `lh $4, -0xB90` is the compare operand of
 * the guard, left sitting in $4. */

extern const u8 D_00525A30;
extern u8 D_004B2570[0x10];            /* main-image object; retail materialises it
                                    as lui/addiu, i.e. an ADDRESS not an int */

typedef struct Panel {
    u8   pad000[8];
    s32  f008;
} Panel;
extern Panel D_00527C40;          /* +0x08 = D_00527C48 */
extern Panel D_00527C60;          /* +0x08 = D_00527C68 */

/* D_00527C98 / D_00527CA0 / D_00527CA1 are MEMBERS of D_00527C80, not small
 * globals: retail addresses all three with lui/%lo, and a separate 1/4-byte
 * extern lands in SMALL DATA and comes out GPREL16 -- right instruction, wrong
 * relocation, and four words short.  Same for D_004B2570, which needs a size
 * over the small-data threshold to be materialised as an address. */
typedef struct Obj3 {
    u8   pad000[0x18];
    s32  f018;
    u8   pad01C[4];
    u8   b020 : 1;
    s8   f021;
} Obj3;
extern Obj3 D_00527C80;

extern s16   D_004845E0;          /* gp - 0xB90 */
extern u8    D_004845DC;          /* gp - 0xB94 */
extern void *D_004845AC;          /* gp - 0xBC4 */
extern s32   D_004845A8;          /* gp - 0xBC8 */
extern s16   D_004845B8;          /* gp - 0xBB8 */
extern s32   D_004845BC;          /* gp - 0xBB4 */
extern s32   D_004845C0;          /* gp - 0xBB0 */
extern s16   D_00480638;          /* gp - 0x4B38 */
extern f32   D_0047D934;          /* gp - 0x783C */

typedef struct Ent {
    u8   pad000[4];
    s32  f004;
    u8   pad008[2];
    u16  f00A;
} Ent;

typedef struct Slot {
    void *f00;
    s16   f04;
    s16   f06;
    s16   f08;
    s16   f0A;
    u16   f0C;
} Slot;

typedef struct Wid {
    u8   pad000[0x24];
    s32  f024;
} Wid;

extern void func_1319A8(s32 dst, const u8 *src, s32 n);
extern void func_157CA0(s32 a, s32 b, f32 x);
extern s32  func_15DE40(void);
extern void func_183950(void *a, s32 b);
extern void func_183960(void *a);
extern void func_183D50(void *a, s32 b, s32 c, s32 d);
extern s32  func_1FEDF0(void);
extern s32  func_206A40(void);
extern void func_28B660(void *p, Slot *s);
extern void func_28E0C0(Obj3 *p, void *q, u64 h);
extern void func_28EB70(Obj3 *p, s32 n, Panel *q);
extern void func_28EC80(Obj3 *p);
extern void func_28ED70(void *p);
extern void func_28EDE0(void *p, s32 id, s32 a);
extern void func_2901D0(Panel *p, s32 n, s32 c, s32 d);
extern void func_290390(Panel *p, void *q, u64 h);
extern void func_290450(Panel *p);
extern Wid *func_290460(void *p, u16 id);
extern void func_290690(Panel *p, s32 id, f32 x, f32 y, f32 z);
extern f32  func_290770(Panel *p, s32 id);
extern void func_2907A0(Panel *p, s32 id, f32 x);
extern void func_290F60(Panel *p, s32 id, s32 c, s32 d);
extern void func_291110(Panel *p, s32 id, s32 c, s32 d);
extern void func_2912E0(Panel *p);
extern void func_2913A0(Panel *p);
extern s32  func_3EEF10(s32 a);
extern Ent *func_42C040(s32 a, s32 b);
extern Ent *func_42C500(s32 a, s32 b);
extern s32  func_42C950(s32 a, s32 b);
extern void normal_ShopMenuResPoll_50ae40(void);

void normal_ShopMenuStep_50a6f0(void)
{
    Slot sl;
    Ent *e;
    s32 o;
    s32 n;
    u64 h;
    s32 dst;
    s32 i;
    s32 t;

    if (D_004845E0 != 0) {
        if (D_004845DC != 0) {
            o = func_206A40();
            e = func_42C500(o, 5);
            n = e->f004;
            h = ((u64)e->f00A << 48) >> 50;
            func_2912E0(&D_00527C40);
            func_290390(&D_00527C40, D_004845AC, h);
            func_2901D0(&D_00527C40, n, 0, 0);
            D_00527C40.f008 = 0x32D;
            func_290450(&D_00527C40);
            sl.f00 = &D_00527C40;
            sl.f04 = 0x3D;
            sl.f06 = 0x3C;
            sl.f08 = 0x3E;
            sl.f0A = 0x38;
            sl.f0C = 0x39;
            func_28B660(D_004845AC, &sl);
            dst = func_290460(sl.f00, sl.f0C)->f024;
            i = 0;
            do {
                func_1319A8(dst, &D_00525A30, 0x20);
                i += 1;
                dst += 0x20;
            } while (i < 8);
            e = func_42C500(o, 6);
            n = e->f004;
            h = ((u64)e->f00A << 48) >> 50;
            func_2912E0(&D_00527C60);
            func_290390(&D_00527C60, D_004845AC, h);
            func_2901D0(&D_00527C60, n, 0, 0);
            D_00527C60.f008 = 0x32D;
            func_290450(&D_00527C60);
            e = func_42C040(o, 5);
            n = e->f004;
            h = ((u64)e->f00A << 48) >> 50;
            func_28EC80(&D_00527C80);
            func_28E0C0(&D_00527C80, D_004845AC, h);
            func_28EB70(&D_00527C80, n, &D_00527C40);
            D_00527C80.f018 = D_004845A8;
            D_00527C80.b020 = 0;
            D_00527C80.f021 = 0;
            D_004845BC = 0;
            D_004845C0 = 0;
            D_004845B8 = 0;
            D_004845C0 = func_42C950(o, 5);
            func_183960(D_004B2570);
            func_183D50(D_004B2570, 0xF00C, 0xC, 7);
            func_183950(D_004B2570, 0x78);
            func_291110(&D_00527C40, 4, 0, 1);
            func_2907A0(&D_00527C40, 4, 0.0f);
            func_290F60(&D_00527C40, 0xE, 0, -0x1E);
            func_291110(&D_00527C40, 1, 1, 1);
            func_290690(&D_00527C40, 1, 1.0f, D_0047D934, 0.0f);
            func_291110(&D_00527C40, 3, 1, 1);
            func_290690(&D_00527C40, 3, 1.0f, D_0047D934, 0.0f);
            D_004845DC = 0;
            D_004845E0 = 2;
        }
        if (D_00480638 == 1) {
            if (D_004845E0 == 2) {
                t = func_1FEDF0();
                if (!(func_290770(&D_00527C40, 1) < 1.0f)) {
                    if (func_3EEF10(t) != 0) {
                        D_00480638 = 0;
                        func_28EDE0(&D_004845B8, 0x7531, 1);
                    }
                }
            }
        }
        normal_ShopMenuResPoll_50ae40();
        if (D_004845E0 == 2) {
            t = func_15DE40();
            if (t != 0) {
                func_157CA0(t, 0x32E, 1.0f);
            }
            func_2913A0(&D_00527C40);
            func_2913A0(&D_00527C60);
            func_28ED70(&D_004845B8);
        }
    }
}
