/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelFlashUpdate_4f50f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F50F0 (512 B / 128 words incl. 2 pad nops) -- the roster panel's
 * per-frame fade tick.  A global phase angle advances by 0.1 and wraps at pi;
 * every live row's own timer counts down by 0.0523 and re-tints its i*7+6
 * widget, and every row still flagged in f360 gets the shared phase tint.
 *
 * The six gp floats are MAIN's `.lit4` POOL, not variables
 * (levers.d/mwcc-float-literal-pool.md):
 *   -0x772C 0x0047DA44 0.1f      -0x7F74 0x0047D1FC 3.14159274f
 *   -0x76F4 0x0047DA7C 0.4f      -0x7EE8 0x0047D288 0.6f
 *   -0x770C 0x0047DA64 0.0523f   -0x7F28 0x0047D248 0.7f
 * `mtc1 $0,$f1 / adda.s $f1,$f2 / madd.s $f20,$f3,$f0` is
 * levers.d/ps2-float-accumulator.md's `x + (y * z)`, i.e. 0.4f + 0.6f*s.
 * ⚠ dv_osbuild.py does NOT apply t_lit4.patch -- score this one with
 * build/wf-normal/mg/mg_score.py.
 */
typedef struct Sub { u8 pad00[0x8]; s64 f08; } Sub;
typedef struct Ent { u8 pad00[0x24]; Sub *f24; } Ent;
typedef struct Pan {
    u8  pad000[0x2C0];
    f32 f2C0[40];
    u8  f360[0x18];
    s16 f378;
} Pan;

extern f32   D_00484418;          /* gp - 0xD58 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudPanelFlashUpdate_4f50f0(Pan *p)
{
    f32 *q;
    s32  n;
    s32  i;
    u16  id;
    s32  k;
    s32  base;
    Ent *e;
    Sub *s;
    f32  t;
    f32  w;

    if (p->f378 == 0) {
        return;
    }
    D_00484418 += 0.1f;
    if (D_00484418 >= 3.14159274f) {
        D_00484418 = 0.0f;
    }
    t = 0.4f + 0.6f * Sinf_128fd0(D_00484418);
    if (GetGameData_1fede0() == 0) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50();
    for (i = 0; i < n; i++) {
        q = &p->f2C0[i];
        if (*q == -1.0f) {
            continue;
        }
        w = 1.0f + Sinf_128fd0(*q);
        base = i * 7;
        id = (u16)(base + 6);
        *q -= 0.0523f;
        UiSetWidgetColor_2905b0(p, id, w, w, w, 1.0f);
        e = ((Ent *)UiFindWidget_290460(p, (u16)(base + 11)));
        if (e != 0) {
            s = e->f24;
            if (s != 0 && s->f08 <= 0) {
                p->f360[i] = 0;
                UiSetWidgetColor_2905b0(p, id, 0.7f, 0.7f, 0.7f, -1.0f);
            }
        }
        if (*q <= 0.0f) {
            *q = -1.0f;
        }
    }
    for (k = 0; k < n; k++) {
        if (p->f360[k] != 0) {
            UiSetWidgetColor_2905b0(p, (u16)(k * 7 + 6), t, t, t, -1.0f);
        }
    }
}
