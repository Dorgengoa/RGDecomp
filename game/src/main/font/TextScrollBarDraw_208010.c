/* rgp:protos */
#define RGP_SELF_TextScrollBarDraw_208010 1
#define RGP_SELF_clr 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct Col { f32 r; f32 g; f32 b; f32 a; } Col;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

void TextScrollBarDraw_208010(void *ctx, s32 x, s32 y, s32 cx, s32 cy, s32 w, s32 h, s32 pad,
                  f32 r, f32 g, f32 b, f32 a, f32 a2, s32 total, s32 start, s32 vis)
{
    Col c1 __attribute__((aligned(16)));
    Col c2 __attribute__((aligned(16)));
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 hgt;
    f32 scale;
    s32 len;
    s32 pos;

    if (ctx == 0) {
        return;
    }
    GetSysTextStyle_313570();
    x0 = x + cx * 9 - pad + 1;
    y0 = y + cy * 15 - pad + 3;
    x1 = pad + (x + (cx + w) * 9) + 1;
    y1 = pad + (y + (cy + h) * 15);
    hgt = y1 - y0 + 1;
    clr(&c1, sizeof(c1));
    c1.r = r;
    scale = (f32)hgt / (f32)total;
    c1.a = a2;
    c1.g = g;
    pos = (s32)((f32)y0 + (f32)start * scale);
    c1.b = b;
    len = (s32)((f32)vis * scale);
    if (len <= 0) {
        len = 1;
    }
    if (hgt * total % vis > 0) {
        len++;
    }
    clr(&c2, sizeof(c2));
    c2.r = r;
    c2.g = g;
    c2.b = b;
    c2.a = a;
    GsPktOpenPrim_13f730(ctx, 6);
    GsPktSetRGBAQVec_13edd0(ctx, &c1);
    GsPktSetXYZf_13f060(ctx, x0, y0, 1.0f);
    GsPktSetXYZf_13f060(ctx, x1, y1, 1.0f);
    GsPktClose_13f5b0(ctx);
    GsPktOpenPrim_13f730(ctx, 6);
    GsPktSetRGBAQVec_13edd0(ctx, &c2);
    GsPktSetXYZf_13f060(ctx, x0, pos, 1.0f);
    GsPktSetXYZf_13f060(ctx, x1, pos + len - 1, 1.0f);
    GsPktClose_13f5b0(ctx);
}
