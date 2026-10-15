#include "types.h"
/* normal 0x00520500 -- the SAME function as normal_FUN_0050E980 (MERGED) with
 * a different widget bank: gp handle -0x850, ids 0x7536/0x7537 rather than
 * 0x39/0x3A, and the two row lists fetched with func_28F2B0(p, id, 0) directly
 * instead of func_290460(p, id)->f24.  It inherits 0050E980's ONE lever --
 * `(u32)i * 2` at the FIRST call site of each arm, which splits the address CSE
 * retail declines to make ([[normal-cse-cost-split]]); spelled `i * 2` at both
 * sites mwcc keeps it in a callee-saved register across the `jal` and the unit
 * reads 167 bad at the right length.  Written as a substitution off 0050E980's
 * source and byte-identical on the first build.
 */
typedef struct Item {
    s16  f00;
    s16  f02;
    u8   pad04[4];
    s64  f08;
    u8   pad10[0x1C - 0x10];
    s16  f1C;
    s16  f1E;
} Item;

typedef struct Ctx  { u8 pad00[0x18]; void *f18; } Ctx;

extern void *D_00484920;          /* gp - 0x850 */
extern Item *func_28F2B0(void *p, s32 id, s32 a);
extern s32   D_004659E8[];        /* main-image count, addressed lui/%lo */

extern Ctx  *func_1FEDE0(void);
extern void  func_28F710(void *p, s32 id, s32 c, s32 d, s32 e, s32 f, s32 g,
                         s32 h, s32 i, s32 j, s32 k);
extern void  func_2905B0(void *p, s32 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern s32   func_3C7BA0(void *p, s32 a, s32 b, s32 c);

s32 normal_ThinkMenuTabsLayout_520500(s32 id, s32 sel)
{
    Ctx  *c;
    Item *a;
    Item *b;
    s32   n;
    s32   i;
    s32   j;

    c = func_1FEDE0();
    n = D_004659E8[0];
    for (i = 0; i < n; i++) {
        if (i == sel) {
            func_28F710(D_00484920, id, i * 42 + 0x1B, -0x1A, 0x16, 0x29, 0x88, 1,
                        0x16, 0x29, (u32)i * 2);
            func_28F710(D_00484920, id, i * 42 + 0x31, -0x1A, 0x16, 0x29, 0xA6, 1,
                        0x16, 0x29, i * 2 + 1);
        } else {
            func_28F710(D_00484920, id, i * 42 + 0x1B, -0x18, 0x16, 0x1B, 0x88, 0x2B,
                        0x16, 0x1B, (u32)i * 2);
            func_28F710(D_00484920, id, i * 42 + 0x31, -0x18, 0x16, 0x1B, 0xA6, 0x2B,
                        0x16, 0x1B, i * 2 + 1);
        }
    }
    func_2905B0(D_00484920, 0x7536, 0.5f, 0.5f, 0.5f, 1.0f);
    a = func_28F2B0(D_00484920, 0x7536, 0);
    if (a == 0) {
        return 0;
    }
    b = func_28F2B0(D_00484920, 0x7537, 0);
    if (b == 0) {
        return 0;
    }
    for (j = 0; j < 7; j++) {
        if (j == sel) {
            if (j < n) {
                b->f00 = j * 42 + 0x3B;
                b->f02 = -0xC;
                b->f1C = 0xA;
                b->f1E = 0x10;
                b->f08 = func_3C7BA0(c->f18, 0, j, 0);
            } else {
                b->f00 = -1;
            }
        } else {
            a->f00 = j * 42 + 0x3B;
            a->f02 = -0xC;
            a->f1C = 0xA;
            a->f1E = 0x10;
            if (j < n) {
                a->f08 = func_3C7BA0(c->f18, 0, j, 0);
            }
            if (j >= n) {
                a->f00 = -1;
            }
            a++;
        }
    }
    func_291110(D_00484920, 0x7536, 1, 1);
    return 1;
}
