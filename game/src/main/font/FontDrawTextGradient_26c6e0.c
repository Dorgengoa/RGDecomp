/* rgp:protos */
#define RGP_SELF_FontDrawTextGradient_26c6e0 1
#define RGP_SELF_GetA 1
#define RGP_SELF_GetB 1
#define RGP_SELF_GsDrawTexQuadGradient_26e8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct RGBAQ {
    __extension__ unsigned char r : 8;
    unsigned char  : 0, g : 8;
    unsigned char  : 0, b : 8;
    unsigned char  : 0, a : 8;
    unsigned int q : 32;
} __attribute__((aligned(8))) RGBAQ;

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
extern s32 strlen(const char *);
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
extern void FontGetGlyphRect_26e040(V4 *, void *, u16);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void GsDrawTexQuadGradient_26e8a0(s32, s32, V4 *, R4 *, s32, C8, C8, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/

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
    C8 c1 __attribute__((aligned(16)));
    C8 c2 __attribute__((aligned(16)));
    R4 rc __attribute__((aligned(16)));
    V4 uva __attribute__((aligned(16)));
    V4 uvb __attribute__((aligned(16)));
    V4 ta __attribute__((aligned(16)));
    V4 tb __attribute__((aligned(16)));
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
    gw = ((s32)DrawListBeginPrim_141b00(ctx));
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
            if (((short)TextStyleGetZEnable_26e410(f))) {
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
            a = ((short)TextStyleGetAlpha_26dd30(f));
            if (((signed char)TextStyleGetFontType_26ede0(f)) == 0) {
                a = (a - 0x40) * 2;
                if (a < 0) {
                    a = 0;
                }
            }
            FontDrawGlyphOutline_26e450(f, gw, &rc, &uva, a);
            GsPktClose_13f5b0(gw);
            FontPktSetTextState_26fc80(gw);
            if (((short)TextStyleGetZEnable_26e410(f))) {
                GsPktSetOriginMode_13e2f0(gw, 0);
                GsPktEnableZTest_13e460(gw, 1);
                GsPktSetZTest_13e450(gw, 2);
                ch = ((short)TextStyleGetGradientMode_26e320(f));
                px = ((short)TextStyleGetAlpha_26dd30(f));
                GsDrawTexQuadGradient_26e8a0(gw, tex, &uva, &rc, ch, c1, c2, px, TextStyleGetZ_26e430(f));
            } else {
                ch = ((short)TextStyleGetGradientMode_26e320(f));
                GsDrawTexQuadGradient_26e8a0(gw, tex, &uva, &rc, ch, c1, c2, ((short)TextStyleGetAlpha_26dd30(f)), 0);
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
                RGBAQ rc_ __attribute__((aligned(16))) = { 0x80, 0x80, 0x80, ((short)TextStyleGetAlpha_26dd30(f)), 0 };
                FontDrawGaiji_26dd50(f, gw, icon, px, py, __builtin_bit_cast(long long, (rc_)));
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
        if (((short)TextStyleGetZEnable_26e410(f))) {
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
        a = ((short)TextStyleGetAlpha_26dd30(f));
        if (((signed char)TextStyleGetFontType_26ede0(f)) == 0) {
            a = (a - 0x40) * 2;
            if (a < 0) {
                a = 0;
            }
        }
        FontDrawGlyphOutline_26e450(f, gw, &rc, &uvb, a);
        GsPktClose_13f5b0(gw);
        FontPktSetTextState_26fc80(gw);
        if (((short)TextStyleGetZEnable_26e410(f))) {
            GsPktSetOriginMode_13e2f0(gw, 0);
            GsPktEnableZTest_13e460(gw, 1);
            GsPktSetZTest_13e450(gw, 2);
            ch = ((short)TextStyleGetGradientMode_26e320(f));
            px = ((short)TextStyleGetAlpha_26dd30(f));
            GsDrawTexQuadGradient_26e8a0(gw, tex, &uvb, &rc, ch, c1, c2, px, TextStyleGetZ_26e430(f));
        } else {
            ch = ((short)TextStyleGetGradientMode_26e320(f));
            GsDrawTexQuadGradient_26e8a0(gw, tex, &uvb, &rc, ch, c1, c2, ((short)TextStyleGetAlpha_26dd30(f)), 0);
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
