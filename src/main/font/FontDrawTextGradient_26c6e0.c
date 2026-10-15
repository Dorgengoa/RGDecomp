#include "types.h"

typedef struct RGBAQ {
    u64 r : 8;
    u64 g : 8;
    u64 b : 8;
    u64 a : 8;
    u64 q : 32;
} RGBAQ;

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct R4 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} R4;

typedef struct C8 {
    u64 v;
} C8;

extern s32 GetDrawCtx_15de80(void);
extern s32 DrawListBeginPrim_141b00(s32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void FontSetScissor_26e380(void *, s32);
extern void FontResetScissor_26e340(void *, s32);
extern void TextStyleGetRgba_26f2a0(C8 *, void *);
extern void TextStyleGetGradRgba_26f200(C8 *, void *);
extern s32 strlen(const char *);
extern s32 FontMapChar_26ed60(void *, s32);
extern s32 FontIsAsciiCode_26ed80(void *, s32);
extern void FontGetCharCellSize_26f310(void *, s32 *, s32 *, u16);
extern void FontGetGlyphWidth_26f420(void *, u16);
extern void FontGetLineHeight_26f3e0(void *);
extern s32 FontMatchSymbolTag_26ef40(char *, u16 *, s32 *);
extern s32 FontMatchGaijiTag_26ef90(char *, u16 *, s32 *);
extern void GsPktSetup2DState_26fdc0(s32);
extern void FontPktSetTextState_26fc80(s32);
extern s32 TextStyleGetZEnable_26e410(void *);
extern s32 FontGetGlyphPage_26e240(void *, u16);
extern void FontGetGlyphRect_26e040(V4 *, void *, u16);
extern s32 TextStyleGetAlpha_26dd30(void *);
extern s32 TextStyleGetFontType_26ede0(void *);
extern void FontDrawGlyphOutline_26e450(void *, s32, R4 *, V4 *, s32);
extern s32 TextStyleGetGradientMode_26e320(void *);
extern s32 TextStyleGetZ_26e430(void *);
extern void GsDrawTexQuadGradient_26e8a0(s32, s32, V4 *, R4 *, s32, C8, C8, s32, s32);
extern void FontDrawGaiji_26dd50(void *, s32, u16, s32, s32, RGBAQ);
extern s16 FontGetGaijiWidth_26f890(void *, u16);
extern s32 FontFindCode_26ee00(void *, char *);

/* colour words are sret temps behind inline getters (temps allocated after the RGBAQ initializer) */
static inline C8 GetA(void *f) { C8 t; TextStyleGetRgba_26f2a0(&t, f); return t; }
static inline C8 GetB(void *f) { C8 t; TextStyleGetGradRgba_26f200(&t, f); return t; }

void FontDrawTextGradient_26c6e0(void *f, char *str, s32 x, s32 y)
{
    u16 code;
    u16 icon;
    s32 w;
    s32 h;
    s32 n;
    s32 w2;
    s32 h2;
    s32 n2;
    C8 c1;
    C8 c2;
    R4 rc;
    V4 uva;
    V4 uvb;
    V4 ta;
    V4 tb;
    s32 ctx;
    s32 gw;
    s32 scrw;
    s32 scrh;
    s32 len;
    s32 dx;
    s32 dy;
    s32 i;
    char *p;
    s32 ch;
    s32 wide;
    s32 px;
    s32 py;
    s32 tex;
    s32 a;
    u16 c;

    ctx = GetDrawCtx_15de80();
    gw = DrawListBeginPrim_141b00(ctx);
    FontSetScissor_26e380(f, gw);
    scrw = DrawEnvGetWidth_1451e0(ctx);
    scrh = DrawEnvGetHeight_1451d0(ctx);
    c1 = GetA(f);
    c2 = GetB(f);
    len = strlen(str);
    dx = 0;
    dy = 0;
    for (i = 0; i < len; ) {
        p = str + i;
        ch = FontMapChar_26ed60(f, *p);
        wide = FontIsAsciiCode_26ed80(f, ch) != 0;
        FontGetCharCellSize_26f310(f, &w, &h, ch);
        FontGetGlyphWidth_26f420(f, ch);
        FontGetLineHeight_26f3e0(f);
        px = x + dx;
        if (px < -16 || px > scrw + 16 || (py = y + dy) < -16 || scrh + 16 < py) {
            dx += w;
            if (wide) {
                i++;
            } else {
                i += 2;
            }
            continue;
        }
        if (FontMatchSymbolTag_26ef40(p, &code, &n)) {
            GsPktSetup2DState_26fdc0(gw);
            if (TextStyleGetZEnable_26e410(f)) {
                GsPktSetOriginMode_13e2f0(gw, 0);
                GsPktEnableZTest_13e460(gw, 1);
                GsPktSetZTest_13e450(gw, 2);
                GsPktSetGouraud_13e3b0(gw, 1);
            }
            GsPktOpenPrim_13f730(gw, 6);
            tex = FontGetGlyphPage_26e240(f, code);
            if (tex) {
                GsPktSetTexture_13ec00(gw, tex);
            }
            FontGetGlyphRect_26e040(&ta, f, code);
            *(V4 *)&uva = ta;
            rc.a = px;
            rc.b = py;
            rc.c = ((R4 *)&uva)->c;
            rc.d = ((R4 *)&uva)->d;
            a = TextStyleGetAlpha_26dd30(f);
            if (TextStyleGetFontType_26ede0(f) == 0) {
                a = (a - 0x40) * 2;
                if (a < 0) {
                    a = 0;
                }
            }
            FontDrawGlyphOutline_26e450(f, gw, &rc, &uva, a);
            GsPktClose_13f5b0(gw);
            FontPktSetTextState_26fc80(gw);
            if (TextStyleGetZEnable_26e410(f)) {
                GsPktSetOriginMode_13e2f0(gw, 0);
                GsPktEnableZTest_13e460(gw, 1);
                GsPktSetZTest_13e450(gw, 2);
                ch = TextStyleGetGradientMode_26e320(f);
                px = TextStyleGetAlpha_26dd30(f);
                GsDrawTexQuadGradient_26e8a0(gw, tex, &uva, &rc, ch, c1, c2, px, TextStyleGetZ_26e430(f));
            } else {
                ch = TextStyleGetGradientMode_26e320(f);
                GsDrawTexQuadGradient_26e8a0(gw, tex, &uva, &rc, ch, c1, c2, TextStyleGetAlpha_26dd30(f), 0);
            }
            FontGetCharCellSize_26f310(f, &w2, &h2, code);
            dx += w2;
            i += n;
            continue;
        }
        if (FontMatchGaijiTag_26ef90(p, &icon, &n2)) {
            GsPktSetup2DState_26fdc0(gw);
            GsPktOpenPrim_13f730(gw, 6);
            {
                /* local initializer: 0x80,0x80,0x80,_,0 copied from .sdata D_0047E9A0 (-sdatathreshold 16) */
                RGBAQ rc_ = { 0x80, 0x80, 0x80, TextStyleGetAlpha_26dd30(f), 0 };
                FontDrawGaiji_26dd50(f, gw, icon, px, py, rc_);
            }
            GsPktClose_13f5b0(gw);
            dx += FontGetGaijiWidth_26f890(f, icon);
            i += n2;
            continue;
        }
        if (ch == -2) {
            dx = 0;
            i++;
            dy += h;
            continue;
        }
        if (wide) {
            c = ch;
        } else {
            c = FontFindCode_26ee00(f, p);
        }
        GsPktSetup2DState_26fdc0(gw);
        if (TextStyleGetZEnable_26e410(f)) {
            GsPktSetOriginMode_13e2f0(gw, 0);
            GsPktEnableZTest_13e460(gw, 1);
            GsPktSetZTest_13e450(gw, 2);
            GsPktSetGouraud_13e3b0(gw, 1);
        }
        GsPktOpenPrim_13f730(gw, 6);
        tex = FontGetGlyphPage_26e240(f, c);
        if (tex) {
            GsPktSetTexture_13ec00(gw, tex);
        }
        FontGetGlyphRect_26e040(&tb, f, c);
        *(V4 *)&uvb = tb;
        rc.a = px;
        rc.b = py;
        rc.c = ((R4 *)&uvb)->c;
        rc.d = ((R4 *)&uvb)->d;
        a = TextStyleGetAlpha_26dd30(f);
        if (TextStyleGetFontType_26ede0(f) == 0) {
            a = (a - 0x40) * 2;
            if (a < 0) {
                a = 0;
            }
        }
        FontDrawGlyphOutline_26e450(f, gw, &rc, &uvb, a);
        GsPktClose_13f5b0(gw);
        FontPktSetTextState_26fc80(gw);
        if (TextStyleGetZEnable_26e410(f)) {
            GsPktSetOriginMode_13e2f0(gw, 0);
            GsPktEnableZTest_13e460(gw, 1);
            GsPktSetZTest_13e450(gw, 2);
            ch = TextStyleGetGradientMode_26e320(f);
            px = TextStyleGetAlpha_26dd30(f);
            GsDrawTexQuadGradient_26e8a0(gw, tex, &uvb, &rc, ch, c1, c2, px, TextStyleGetZ_26e430(f));
        } else {
            ch = TextStyleGetGradientMode_26e320(f);
            GsDrawTexQuadGradient_26e8a0(gw, tex, &uvb, &rc, ch, c1, c2, TextStyleGetAlpha_26dd30(f), 0);
        }
        dx += w;
        if (wide) {
            i++;
        } else {
            i += 2;
        }
    }
    FontResetScissor_26e340(f, gw);
    DrawListEndPrim_141a20(ctx);
}
