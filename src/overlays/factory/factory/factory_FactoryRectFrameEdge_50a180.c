#include "types.h"

/* factory.bin overlay, 0x0050A180 -- draw the conveyor belt run between two
 * points as `n' unit quads: build the segment matrix, then per step transform
 * the four corner points of the template and emit one sprite.  820 bytes.
 */

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Mtx4 {
    Vec4 v[4];
} Mtx4;

typedef union W {
    f32 f;
    s32 i;
} W;



typedef struct Pt2 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
} Pt2;

extern void func_1CBE40(Mtx4 *m);
extern void func_1CB9F0(Mtx4 *m, Vec4 *a, Vec4 *b);
extern f32  func_1CB4C0(Vec4 *v);
extern f32  func_128E30(f32 x);
extern void func_1CBBF0(Vec4 *d, Vec4 *s, f32 k);
extern void func_1CB510(Mtx4 *d, Mtx4 *s, f32 k);
extern void func_1CB8E0(Vec4 *d, Mtx4 *m, Vec4 *v);
extern s32  func_15D340(Pt2 *d, Vec4 *v);
extern void func_13F730(s32 g, s32 n);
extern void func_13EDD0(s32 g, s32 v);
extern void func_13EC00(s32 g, s32 v);
extern void func_13ED60(s32 g, s32 x, s32 y);
extern void func_13EEB0(s32 g, Pt2 *p);
extern void func_13F5B0(s32 g);
extern f32 D_00480E60;
extern f32 D_00480E64;
extern f32 D_00480E68;
extern f32 D_00480E6C;
extern const s32 D_0050C930[16];

void factory_FactoryRectFrameEdge_50a180(s32 unused, s32 g, s32 col, s32 row, s32 pal,
                          f32 sc, f32 x0, f32 y0, f32 x1, f32 y1, f32 z)
{
    Mtx4 m;
    volatile W rc[4];
    f32  pts[16];
    Vec4 tp[4];
    Pt2  op[4];
    s32  i;
    s32  n;
    s32  ty;
    s32  by;
    s32  bx;
    const s32 *sp;
    s32  *dp;
    s32  k;

    func_1CBE40(&m);
    m.v[2].x = x1 - x0;
    m.v[2].y = 0.0f;
    m.v[2].z = y1 - y0;
    m.v[2].w = 0.0f;
    func_1CB9F0(&m, &m.v[1], &m.v[2]);
    m.v[3].x = x0;
    m.v[3].y = z;
    m.v[3].z = y0;
    m.v[3].w = 1.0f;
    n = (s32)func_128E30(0.5f + ((0.5f * func_1CB4C0(&m.v[2])) / sc));
    if (n <= 0) {
        return;
    }
    func_1CBBF0(&m.v[2], &m.v[2], (f32)n);
    func_1CB510(&m, &m, sc);
    i = 0;
    ty = row * 0x18;
    *(Vec4 *)rc = *(Vec4 *)&D_00480E60;
    by = (ty + rc[3].i) - 1;
    bx = (rc[0].i + rc[2].i) - 1;
    while (i < n) {
        sp = D_0050C930;
        dp = (s32 *)pts;
        k = 8;
        do {
            dp[0] = sp[0];
            dp[1] = sp[1];
            sp += 2;
            dp += 2;
            k--;
        } while (k > 0);
        pts[2] = (f32)i;
        pts[6] = (f32)i;
        pts[10] = (f32)(i + 1);
        pts[14] = (f32)(i + 1);
        func_1CB8E0(&tp[0], &m, (Vec4 *)&pts[0]);
        func_1CB8E0(&tp[1], &m, (Vec4 *)&pts[4]);
        func_1CB8E0(&tp[2], &m, (Vec4 *)&pts[8]);
        func_1CB8E0(&tp[3], &m, (Vec4 *)&pts[12]);
        if (func_15D340(&op[0], &tp[0]) != 0) {
            if (func_15D340(&op[1], &tp[1]) != 0) {
                if (func_15D340(&op[2], &tp[2]) != 0) {
                    if (func_15D340(&op[3], &tp[3]) != 0) {
                        func_13F730(g, 4);
                        func_13EDD0(g, pal);
                        func_13EC00(g, col);
                        func_13ED60(g, rc[0].i, ty);
                        func_13EEB0(g, &op[0]);
                        func_13ED60(g, rc[0].i, by);
                        func_13EEB0(g, &op[1]);
                        func_13ED60(g, bx, ty);
                        func_13EEB0(g, &op[2]);
                        func_13ED60(g, bx, by);
                        func_13EEB0(g, &op[3]);
                        func_13F5B0(g);
                    }
                }
            }
        }
        i++;
    }
}
