#include "types.h"
/* normal 0x004F2FF0 -- builds one rotated, tinted sprite quad and submits it.
 * session 31, lane n31j.  254 words, 6 integer parameters ($4..$9) plus ONE
 * float parameter in $f12 (the angle), five callee-saved GPRs and five
 * callee-saved FPRs (f20 = (f32)o->f00, f21 = (f32)o->f02, f22 = angle then
 * sin, f23 = h/2, f24 = w/2).
 *
 * Read off the listing:
 *  - every counted loop is BOTTOM-tested -> `do { } while`.
 *  - `mula.s`/`madd.s` pairs are `y*sn + x*cs` -- the FIRST product is the one
 *    `mula.s` names ([[ps2-float-accumulator]]).
 *  - `neg.s $f4,$f22` is hoisted OUT of the rotate loop, so retail's second row
 *    is `y*cs + x*(-sn)`; spelled `- x * sn` here.
 *  - the 16-byte `sb`-clear loop that NULL-CHECKS `$29+0x90` is an array
 *    initialiser ([[mwcc-array-initialiser-clear-loop]]) -> `s16 pts[4][2]`
 *    with `= {0}`.
 *  - `sw $0` (not mtc1/swc1) is how mwcc stores a 0.0f, so quad[i][2..3] are
 *    plain `0.0f` stores.
 */

typedef struct Obj {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0xC];
    u16 f1C;
} Obj;

typedef struct Desc {
    u8   pad00[2];
    u16  f02;
    u8   pad04[0x18];
    s16  f1C;
    u8   pad1E[2];
    Obj *f20;
    u8   pad24[0xC];
    f32  f30[4];
} Desc;

extern f32 *func_2904B0(void *w, u16 id);
extern f32  func_290770(void *w, s32 id);
extern f32  func_128FD0(f32 t);
extern f32  func_128D30(f32 t);
extern void func_13E2F0(void *r, s32 v);
extern void func_13E390(void *r, s32 v);
extern void func_13E3B0(void *r, s32 v);
extern void func_13E3D0(void *r, s32 v);
extern void func_13E3E0(void *r, s32 v);
extern void func_13E400(void *r, s32 v);
extern void func_13E430(void *r, s32 v);
extern void func_13E460(void *r, s32 v);
extern void func_13E4D0(void *r, s32 v);
extern void func_13E4F0(void *r, s32 v);
extern void func_13E500(void *r, s32 v);
extern void func_13EC00(void *r, s32 v);
extern void func_13ED60(void *r, s16 x, s16 y);
extern void func_13EE40(void *r, s32 a, s32 b, s32 c, s32 d);
extern void func_13F060(void *r, f32 x, f32 y, f32 z);
extern void func_13F5B0(void *r);
extern void func_13F730(void *r, s32 v);

void normal_FieldHudRadarDrawArrow_4f2ff0(void *w, void *r, Desc *d, s32 ox, s32 oy, s32 pri,
                         f32 ang)
{
    Obj *o;
    f32 *m;
    f32 *q;
    f32  alpha;
    f32  sn;
    f32  cs;
    f32  nsn;
    f32  hw;
    f32  hh;
    f32  fy;
    f32  fx;
    f32  x;
    f32  y;
    s32  u;
    s32  v;
    s32  u2;
    s32  v2;
    s32  i;
    s32  j;
    s32  k;
    s32  n;
    f32  mul[4];
    s32  col[4];
    f32  quad[4][4];

    o = d->f20;
    if ((d->f1C & 1) != 0) {
        return;
    }
    i = 0;
    do {
        mul[i] = d->f30[i];
        i++;
    } while (i < 4);
    m = func_2904B0(w, d->f02);
    if (m != 0) {
        j = 0;
        do {
            mul[j] = mul[j] * *m;
            m++;
            j++;
        } while (j < 4);
    }
    alpha = func_290770(w, 0x25);
    k = 0;
    do {
        col[k] = (s32)(alpha * (128.0f * mul[k]));
        k++;
    } while (k < 4);
    func_13E4F0(r, 1);
    if ((o->f1C & 1) != 0) {
        func_13E4F0(r, 2);
    }
    func_13E500(r, 1);
    func_13E390(r, 0);
    func_13E4D0(r, 1);
    func_13E460(r, 0);
    func_13E400(r, 1);
    func_13E3E0(r, 1);
    func_13E2F0(r, 0);
    if ((o->f1C & 2) != 0) {
        func_13E3D0(r, 1);
    } else {
        func_13E3D0(r, 0);
    }
    func_13E430(r, 1);
    func_13E3B0(r, 0);
    func_13F730(r, 4);
    func_13EC00(r, pri);
    fx = (f32)o->f00;
    fy = (f32)o->f02;
    hw = (f32)o->f04 / 2.0f;
    hh = (f32)o->f06 / 2.0f;
    sn = func_128FD0(ang);
    cs = func_128D30(ang);
    quad[0][0] = -hw;
    quad[0][1] = -hh;
    n = 0;
    quad[0][2] = 0.0f;
    quad[0][3] = 0.0f;
    quad[1][0] = hw;
    quad[1][1] = -hh;
    quad[1][2] = 0.0f;
    quad[1][3] = 0.0f;
    quad[2][0] = -hw;
    quad[2][1] = hh;
    quad[2][2] = 0.0f;
    quad[2][3] = 0.0f;
    quad[3][0] = hw;
    quad[3][1] = hh;
    quad[3][2] = 0.0f;
    quad[3][3] = 0.0f;
    nsn = -sn;
    do {
        q = &quad[n][0];
        x = q[0];
        y = q[1];
        q[0] = x * cs + y * sn;
        q[1] = x * nsn + y * cs;
        n++;
    } while (n < 4);
    func_13EE40(r, col[0], col[1], col[2], col[3]);
    {
        s16 z[4][2] = {0};

        u = o->f08;
        v = o->f0A;
        u2 = u + o->f0C;
        v2 = v + o->f0E;
        z[0][0] = u;
        z[0][1] = v;
        z[1][0] = u2;
        z[1][1] = v;
        z[2][0] = u;
        z[2][1] = v2;
        z[3][0] = u2;
        z[3][1] = v2;
        i = 0;
        do {
            func_13ED60(r, z[i][0], z[i][1]);
            func_13F060(r, (f32)ox + (fx + quad[i][0]),
                        (f32)oy + (fy + quad[i][1]), 0.0f);
            i++;
        } while (i < 4);
    }
    func_13F5B0(r);
}
