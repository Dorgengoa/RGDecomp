/* rgp:protos */
#define RGP_SELF_normal_FieldHudRadarDrawArrow_4f2ff0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
    f32  mul[4] __attribute__((aligned(16)));
    s32  col[4] __attribute__((aligned(16)));
    f32  quad[4][4] __attribute__((aligned(16)));

    o = d->f20;
    if ((d->f1C & 1) != 0) {
        return;
    }
    i = 0;
    do {
        mul[i] = d->f30[i];
        i++;
    } while (i < 4);
    m = ((f32 *)UiGetWidgetColor_2904b0(w, d->f02));
    if (m != 0) {
        j = 0;
        do {
            mul[j] = mul[j] * *m;
            m++;
            j++;
        } while (j < 4);
    }
    alpha = UiGetWidgetAlpha_290770(w, 0x25);
    k = 0;
    do {
        col[k] = (s32)(alpha * (128.0f * mul[k]));
        k++;
    } while (k < 4);
    GsPktSetBlendMode_13e4f0(r, 1);
    if ((o->f1C & 1) != 0) {
        GsPktSetBlendMode_13e4f0(r, 2);
    }
    GsPktSetAlphaBlend_13e500(r, 1);
    GsPktSetAntialias_13e390(r, 0);
    GsPktEnableAlphaTest_13e4d0(r, 1);
    GsPktEnableZTest_13e460(r, 0);
    GsPktSetTextured_13e400(r, 1);
    GsPktSetUseUV_13e3e0(r, 1);
    GsPktSetOriginMode_13e2f0(r, 0);
    if ((o->f1C & 2) != 0) {
        GsPktSetTexFilter_13e3d0(r, 1);
    } else {
        GsPktSetTexFilter_13e3d0(r, 0);
    }
    GsPktSetZWriteMask_13e430(r, 1);
    GsPktSetGouraud_13e3b0(r, 0);
    GsPktOpenPrim_13f730(r, 4);
    GsPktSetTexture_13ec00(r, pri);
    fx = (f32)o->f00;
    fy = (f32)o->f02;
    hw = (f32)o->f04 / 2.0f;
    hh = (f32)o->f06 / 2.0f;
    sn = Sinf_128fd0(ang);
    cs = Cosf_128d30(ang);
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
    GsPktSetRGBAQ_13ee40(r, col[0], col[1], col[2], col[3]);
    {
        s16 z[4][2] __attribute__((aligned(16))) = {0};

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
            GsPktSetUV_13ed60(r, z[i][0], z[i][1]);
            GsPktSetXYZf_13f060(r, (f32)ox + (fx + quad[i][0]),
                        (f32)oy + (fy + quad[i][1]), 0.0f);
            i++;
        } while (i < 4);
    }
    GsPktClose_13f5b0(r);
}
