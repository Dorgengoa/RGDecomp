#include "types.h"

typedef struct Line {
    s32 x;
    s32 y;
    s8 *str;
} Line;

typedef struct Font {
    Line lines[0x80];
    s32 n;
    s32 ctx;
    s32 tex;
    s32 cx;
    s32 cy;
    s32 adv;
    s32 lineh;
    s32 gw;
    s32 gh;
    s32 space;
    u8 pad628[8];
    s32 r;
    s32 g;
    s32 b;
    s32 a;
    f32 alpha;
} Font;

extern s32 GetDrawCtx_15de80(void);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern s32 DrawListBeginPrim_141b00(s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void DrawListEndPrim_141a20(s32);

static inline s32 getch(s8 *s) { if (*s == 0) return 0; return *s; }
void TextGridDrawGlyphMaybe_312da0(Font *o)
{
    s32 c;
    s32 g;
    s32 x0;
    s8 *s;
    s32 i;
    s8 **ps;
    Line *l;
    s32 x;
    s32 ch;
    s32 u;
    s32 *py;
    s32 v;

    if (o->n <= 0) return;
    c = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(c, o->ctx, 1.0f);
    g = DrawListBeginPrim_141b00(c);
    GsPktSetAlphaBlend_13e500(g, 1);
    GsPktSetBlendMode_13e4f0(g, 1);
    GsPktEnableAlphaTest_13e4d0(g, 1);
    GsPktEnableZTest_13e460(g, 0);
    GsPktSetTextured_13e400(g, 1);
    GsPktSetOriginMode_13e2f0(g, 0);
    GsPktSetGouraud_13e3b0(g, 1);
    GsPktOpenPrim_13f730(g, 6);
    GsPktSetTexture_13ec00(g, o->tex);
    GsPktSetRGBAQ_13ee40(g, o->r, o->g, o->b, (s32)((f32)o->a * o->alpha));
    x0 = o->cx;
    for (i = 0; i < o->n; i++) {
        l = &o->lines[i];
        x = l->x;
        ps = &l->str;
        s = l->str;
        if (x != -1 || (py = &l->y, *py != -1)) {
            o->cx = x;
            x0 = x;
            py = &o->lines[(u32)i].y;
            o->cy = o->lines[(u32)i].y;
        }
        while (*s != 0 && (ch = *s) != 0) {
            if (ch == '\n') {
                s++;
                o->cy += o->lineh;
                o->cx = x0;
            } else if (ch == ' ') {
                s++;
                o->cx += o->space;
            } else {
                u = (ch - 0x20) % 16 * o->gw;
                v = (ch - 0x20) / 16 * o->gh;
                GsPktSetUV_13ed60(g, u, v);
                GsPktSetXYZPixel_13f110(g, o->cx, o->cy, 0);
                GsPktSetUV_13ed60(g, u + o->gw, v + o->gh);
                GsPktSetXYZPixel_13f110(g, o->cx + o->gw, o->cy + o->gh, 0);
                s++;
                o->cx += o->adv;
            }
        }
        l = &o->lines[(u32)i];
        *py = -1;
        l->x = -1;
        *ps = 0;
    }
    GsPktClose_13f5b0(g);
    DrawListEndPrim_141a20(c);
    o->n = 0;
    o->cy = 0;
    o->cx = 0;
}
