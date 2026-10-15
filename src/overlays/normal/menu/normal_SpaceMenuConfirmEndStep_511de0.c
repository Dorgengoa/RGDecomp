#include "types.h"

typedef struct DE0A {
    u8  pad00[0x14];
    s8  f14;
    u8  pad15[0x27];
    s16 f3C;
    s16 f3E;
    f32 f40;
    f32 f44;
    s16 f48;
    s16 cell[3][4];
    s16 f62;
    u8  pad64[8];
    s8  f6C;
} DE0A;

typedef struct DE0T {
    s16 f00;
    s16 f02;
    u8  pad04[4];
} DE0T;

typedef struct DE0Q {
    u8  pad00[6];
    s16 f06;
} DE0Q;

typedef struct DE0R {
    u8    pad00[0x20];
    DE0Q *f20;
} DE0R;

extern DE0T D_00525AF0[];

extern u16   D_004806A0[4];       /* gp - 0x4AD0 */
extern u16   D_00480690[4];       /* gp - 0x4AE0 */
extern s32   D_00480678;          /* gp - 0x4AF8 */
extern s16   D_004846A8;          /* gp - 0xAC8  */
extern f32   D_0047D938;          /* gp - 0x7838 */

extern f32  *func_2904B0(DE0A *a, u16 id);
extern void  func_291110(DE0A *a, u16 id, s32 b, s32 c);
extern void  func_2910A0(DE0A *a, u16 id, s32 *ox, s32 *oy);
extern DE0R *func_290460(DE0A *a, u16 id);
extern void  func_2907A0(DE0A *a, u16 id, f32 f);
extern void  func_290F60(DE0A *a, u16 id, s32 x, s32 y);

s32 normal_SpaceMenuConfirmEndStep_511de0(DE0A *a)
{
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    s32 v;
    s32 i;
    s32 key;
    s32 px;
    s32 py;
    s32 id;
    DE0Q *q;
    f32   g0;
    f32   g1;

    if (*func_2904B0(a, 0x25) <= 1.0f) {
        if (a->f62 == 0) {
            func_291110(a, 0x24, 0, 1);
            key = a->cell[a->f3E][a->f3C];
            v = 0;
            for (i = 0; i < 9; i++) {
                if (key == D_00525AF0[i].f00) {
                    v = D_00525AF0[i].f02;
                }
            }
            func_2910A0(a, D_004806A0[(s16)v], &ax, &ay);
            func_290460(a, D_00480690[(s16)v]);
            func_2910A0(a, 0x24, &ax, &ay);
            g0 = D_0047D938;
            g1 = 0.200000003f;
            a->f40 = g0;
            a->f44 = g1;
            func_2907A0(a, 7, 0.6999999881f);
            func_2907A0(a, 0x1E, 0.6999999881f);
            a->f48 = 0;
            a->f14 = 7;
        } else {
            func_291110(a, 0x24, 0, 1);
            key = a->cell[a->f3E][a->f3C];
            v = 0;
            for (i = 0; i < 9; i++) {
                if (key == D_00525AF0[i].f00) {
                    v = D_00525AF0[i].f02;
                }
            }
            func_2910A0(a, D_004806A0[(s16)v], &bx, &by);
            q = func_290460(a, D_00480690[(s16)v])->f20;
            px = bx - 0xA;
            py = by + q->f06 / 2 - 0xA;
            id = 0x28;
            for (i = 0; i < 4; i++) {
                func_290F60(a, (u16)id, px, py);
                id = (s16)(id + 1);
            }
            D_004846A8 = 0;
            D_00480678 = -1;
            a->f14 = 2;
            a->f48 = 0;
            a->f6C = 0;
        }
    }
    return 0;
}
