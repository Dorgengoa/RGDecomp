#include "types.h"
#pragma divbyzerocheck on
#pragma optimization_level 3

typedef struct {
    s16 x;          /* 0x00 */
    s16 y;          /* 0x02 */
    u8 pad4[4];
    s64 val;        /* 0x08 */
    s16 n;          /* 0x10 */
    s16 u;          /* 0x12 */
    s16 v;          /* 0x14 */
    s16 w;          /* 0x16 */
    s16 h;          /* 0x18 */
    s16 flags;      /* 0x1A */
    s16 w2;         /* 0x1C */
    s16 h2;         /* 0x1E */
} Desc;

typedef struct {
    u8 pad0[4];
    s32 tex;        /* 0x04 */
} Src;

extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);

void UiDrawSpritePixelMaybe_292300(Src *src, s32 g, Desc *d, s32 px, s32 py, f32 *color) {
    s32 buf[10];
    s32 col[4];
    s32 v;
    s32 i;
    s32 div;
    s32 sign;
    s32 pos;
    s32 cnt;
    s32 k;
    s32 dg;
    s32 x;
    s32 j;
    s32 y;
    s32 x0;
    s16 w;
    s16 h;
    s32 a;
    s32 b;
    s32 c2;
    s32 c3;
    s32 yy;
    s64 val;
    s16 n;
    s32 uo;
    s32 fl;
    s32 started;
    s32 c1;

    val = d->val;
    n = d->n;
    v = (s32)val;
    div = 1;
    for (i = 0; i < n - 1; i++) {
        div *= 10;
    }
    for (i = 0; i < 10; i++) {
        buf[i] = -1;
    }
    fl = d->flags;
    sign = (fl & 1) != 0;
    if (fl & 0x14) {
        for (k = 0; k < n; k++) {
            buf[k] = -0xFF;
        }
    }
    if (val == 0) {
        if (sign) {
            buf[0] = 0;
        } else {
            buf[n - 1] = 0;
        }
    }
    pos = 0;
    cnt = 0;
    started = 0;
    for (k = 0; k < n; k++) {
        dg = v / div;
        if (dg <= 0 && started == 0) {
            if (sign == 0) {
                pos++;
            }
        } else {
            started = 1;
            buf[pos++] = dg;
            cnt++;
            v -= dg * div;
        }
        div /= 10;
    }
    if (val == 0) {
        cnt++;
    }
    if (cnt == 0) {
        return;
    }
    if (fl & 0x400) {
        GsPktSetTexFilter_13e3d0(g, 1);
    } else {
        GsPktSetTexFilter_13e3d0(g, 0);
    }
    GsPktOpenPrim_13f730(g, 6);
    GsPktSetTexture_13ec00(g, src->tex);
    x = d->x + px;
    y = d->y + py;
    x0 = x;
    for (i = 0; i < 4; i++) {
        col[i] = (s32)(128.0f * color[i]);
    }
    if (d->flags & 0x40) {
        if ((f32)col[3] > 0.0f) {
            col[3] = 0x26;
        }
    }
    if (d->flags & 0x20) {
        col[0] = col[1] = col[2] = 0x80;
    }
    w = d->w;
    h = d->h;
    if (d->flags & 2) {
        w = d->w2;
        h = d->h2;
    }
    if (!sign) {
        x -= w * d->n;
    }
    if (d->flags & 8) {
        if (!(d->flags & 0x14)) {
            x = x0;
            if (cnt != d->n) {
                a = 0;
                b = 0;
                if (cnt > 1) {
                    b = d->n / cnt - 1;
                } else {
                    if (d->n % 2 == 0) {
                        a = d->n / 2 - 1;
                    } else {
                        a = d->n / 2;
                    }
                }
                x -= w * (a + b);
            }
        }
    }
    c3 = col[3];
    c2 = col[2];
    c1 = col[1];
    for (j = 0; j < d->n; j++) {
        dg = *(s32 *)((u32)&buf[j]);
        if (dg == -1) {
            continue;
        }
        if (dg == -0xFF) {
            s32 xx;
            s16 xs;
            s16 ys;
            s16 x1;
            s16 y1;
            if (d->flags & 0x10) {
                if (d->flags & 0x20) {
                    GsPktSetRGBAQ_13ee40(g, 0x55, 0x55, 0x55, c3);
                } else {
                    GsPktSetRGBAQ_13ee40(g, (s32)((f32)col[0] / 1.5f), (s32)((f32)c1 / 1.5f), (s32)((f32)c2 / 1.5f), c3);
                }
            } else {
                GsPktSetRGBAQ_13ee40(g, col[0], c1, c2, c3);
            }
            xx = x + j * w;
            ys = (s16)y;
            xs = (s16)xx;
            y1 = y + h - 1;
            x1 = d->w + xx - 1;
            if (d->flags & 0x200) {
                xx = x + j * d->w;
                xs = (s16)xx;
                x1 = d->w2 + xx - 1;
                y1 = y + d->h2 - 1;
            }
            GsPktSetUV_13ed60(g, d->u, d->v);
            GsPktSetXYZPixel_13f110(g, (s16)xs, (s16)ys, 0);
            GsPktSetUV_13ed60(g, d->u + d->w, d->v + d->h);
            GsPktSetXYZPixel_13f110(g, x1, y1, 0);
        } else {
            s32 xx;
            s16 xs;
            s16 ys;
            s16 x1;
            s16 y1;
            uo = d->w * dg;
            xx = x + j * w;
            ys = (s16)y;
            xs = (s16)xx;
            y1 = y + h - 1;
            x1 = d->w + xx - 1;
            if (d->flags & 0x200) {
                xx = x + j * d->w;
                xs = (s16)xx;
                x1 = d->w2 + xx - 1;
                y1 = y + d->h2 - 1;
            }
            GsPktSetRGBAQ_13ee40(g, col[0], c1, c2, c3);
            GsPktSetUV_13ed60(g, d->u + uo, d->v);
            GsPktSetXYZPixel_13f110(g, (s16)xs, (s16)ys, 0);
            GsPktSetUV_13ed60(g, d->w + (d->u + uo), d->v + d->h);
            GsPktSetXYZPixel_13f110(g, x1, y1, 0);
        }
    }
    GsPktClose_13f5b0(g);
}
