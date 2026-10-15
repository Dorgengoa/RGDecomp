#include "types.h"

typedef struct RGBAQ {
    u64 r : 8;
    u64 g : 8;
    u64 b : 8;
    u64 a : 8;
    u64 q : 32;
} RGBAQ;

/* D_0047E990 = this function's first initializer template (.sdata @N): an ALL-constant bitfield
   initializer is copied MEMBERWISE (ld/extract/RMW chain + lwc1/swc1) because the function has a
   second aggregate initializer (the icon RGBAQ below, template D_0047E998). */
typedef struct RGBAF {
    u64 r : 8;
    u64 g : 8;
    u64 b : 8;
    u64 a : 8;
    f32 q;
} RGBAF;

union GsCol {
    struct {
        u64 r : 8;
        u64 g : 8;
        u64 b : 8;
        u64 a : 8;
        u64 hi : 32;
    } f;
    struct {
        u32 lo;
        f32 q;
    } fq;
    struct {
        s16 rg;
        u8 b;
        u8 a;
        s32 q;
    } s;
    s64 v;
};

struct Font {
    s8 _0[3];
    u8 x3;
    u8 x4;
    s8 _5;
    s16 x6;
    s8 _8[0x10];
    u8 x18;
};

extern "C" {
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void DrawListEndPrim_141a20(s32);
s32 DrawListBeginPrim_141b00(s32);
s32 GetDrawCtx_15de80(void);
void FontDrawTextGradient_26c6e0(Font *, char *, s32, s32);
void TextColorApplyEffectMaybe_26da30(GsCol *, u32, s32);
s32 TextStyleGetAlpha_26dd30(Font *);
void FontDrawGaiji_26dd50(Font *, s32, s32, s32, s32, RGBAQ); /* 3rd param s32: a u16 pins the lhu after the template stores */
void FontDrawGlyph_26de80(Font *, s32, u16, s32, s32, s64, u8, f32);
s32 TextStyleGetGradientMode_26e320(Font *);
void FontResetScissor_26e340(Font *, s32);
void FontSetScissor_26e380(Font *, s32);
s32 FontMapChar_26ed60(Font *, s32);
s32 FontIsAsciiCode_26ed80(Font *, s32);
s32 FontFindCode_26ee00(Font *, char *);
s32 FontMatchSymbolTag_26ef40(char *, u16 *, s32 *);
s32 FontMatchGaijiTag_26ef90(char *, u16 *, s32 *);
u8 TextStyleGetFixedPitch_26f130(Font *);
void FontGetCharCellSize_26f310(Font *, s32 *, s32 *, u16);
u8 FontGetCharWidth_26f4c0(Font *, u16);
s16 FontGetGaijiWidth_26f890(Font *, u16);
void GsPktSetup2DState_26fdc0(s32);
s32 strlen(const char *);
s32 strncmp(const char *, const char *, s32);
extern char D_0045F538[];
extern u8 D_004820B8;
GsCol TextStyleGetRgba_26f2a0(Font *);
void FontDrawText_26cdc0(Font *self, char *str, s32 x, s32 y);
}

void FontDrawText_26cdc0(Font *self, char *str, s32 x, s32 y) {
    u16 ch;
    u16 ch2;
    s32 n;
    s32 adv;
    s32 lh;
    s32 n2;
    s32 a2;
    s32 b2;
    GsCol colB;
    s32 ctx;
    s32 len;
    s32 pk;
    s32 cx;
    s32 cy;
    s32 i;
    s32 code;
    char *p;

    if (str == 0) {
        return;
    }
    len = strlen(str);
    if (len <= 0) {
        return;
    }
    if (TextStyleGetGradientMode_26e320(self)) {
        FontDrawTextGradient_26c6e0(self, str, x, y);
        return;
    }
    /* &colB taken before the sret copy: the address vreg is created early, which is what retail's
       schedule of the colC chain needs (tools: build/s88m/26cd/sim). */
    GsCol *pb = &colB;
    *pb = TextStyleGetRgba_26f2a0(self);
    RGBAF colC = { 0x40, 0x40, 0x80, 0x80, 0.0f };
    TextColorApplyEffectMaybe_26da30(pb, self->x18, self->x6);
    TextColorApplyEffectMaybe_26da30((GsCol *)&colC, self->x18, self->x6);
    ctx = GetDrawCtx_15de80();
    pk = DrawListBeginPrim_141b00(ctx);
    FontSetScissor_26e380(self, pk);
    GsPktSetup2DState_26fdc0(pk);
    GsPktOpenPrim_13f730(pk, 6);
    cx = 0;
    if (TextStyleGetFixedPitch_26f130(self) == 1) {
        cx += (u32)self->x3 >> 1;
    }
    cy = 0;
    for (i = 0; i < len;) {
        p = str + i;
        if (*p == '<') {
            if (strncmp(p, D_0045F538, 7) == 0) {
                i += 7;
                continue;
            }
        }
        if (FontMatchGaijiTag_26ef90(p, &ch, &n)) {
            {
                RGBAQ e = { 0x80, 0x80, 0x80, TextStyleGetAlpha_26dd30(self), 0 };
                FontDrawGaiji_26dd50(self, pk, ch, x + cx, y + cy, e);
            }
            cx += FontGetGaijiWidth_26f890(self, ch);
            i += n;
            continue;
        }
        code = FontMapChar_26ed60(self, *p);
        FontGetCharCellSize_26f310(self, &adv, &lh, code);
        if (code == -2) {
            cx = 0;
            if (TextStyleGetFixedPitch_26f130(self) == 1) {
                cx += (u32)self->x3 >> 1;
                cy += self->x4;
            } else {
                cy += lh;
            }
            i += 1;
            continue;
        }
        if (*p == 0x5C && p[1] == 'n') {
            cx = 0;
            if (TextStyleGetFixedPitch_26f130(self) == 1) {
                cx += (u32)self->x3 >> 1;
                cy += self->x4;
            } else {
                cy += lh;
            }
            i += 2;
            continue;
        }
        if (FontMatchSymbolTag_26ef40(p, &ch2, &n2)) {
            if (TextStyleGetFixedPitch_26f130(self) == 1) {
                s32 hw = (u32)FontGetCharWidth_26f4c0(self, ch2) >> 1;
                if (ch2 >= 0x20 && ch2 < 0x3A) {
                    FontDrawGlyph_26de80(self, pk, ch2, x + cx - hw, y + cy, *(s64 *)&colC, TextStyleGetAlpha_26dd30(self), 1.0f);
                } else {
                    FontDrawGlyph_26de80(self, pk, ch2, x + cx - hw, y + cy, colB.v, TextStyleGetAlpha_26dd30(self), 1.0f);
                }
                cx += self->x3;
            } else {
                FontDrawGlyph_26de80(self, pk, ch2, x + cx, y + cy, colB.v, TextStyleGetAlpha_26dd30(self), 1.0f);
                if (D_004820B8 == 0) {
                    cx += 8;
                } else {
                    FontGetCharCellSize_26f310(self, &a2, &b2, ch2);
                    cx += a2;
                }
            }
            i += n2;
            continue;
        }
        if (FontIsAsciiCode_26ed80(self, code)) {
            if (TextStyleGetFixedPitch_26f130(self) == 1) {
                s32 hw = (u32)FontGetCharWidth_26f4c0(self, code) >> 1;
                if (code >= 0x20 && code < 0x3A) {
                    FontDrawGlyph_26de80(self, pk, code, x + cx - hw, y + cy, *(s64 *)&colC, TextStyleGetAlpha_26dd30(self), 1.0f);
                } else {
                    FontDrawGlyph_26de80(self, pk, code, x + cx - hw, y + cy, colB.v, TextStyleGetAlpha_26dd30(self), 1.0f);
                }
                cx += self->x3;
            } else {
                FontDrawGlyph_26de80(self, pk, code, x + cx, y + cy, colB.v, TextStyleGetAlpha_26dd30(self), 1.0f);
                if (D_004820B8 == 0) {
                    cx += 8;
                } else {
                    cx += adv;
                }
            }
            i += 1;
            continue;
        }
        FontDrawGlyph_26de80(self, pk, (u16)FontFindCode_26ee00(self, p), x + cx, y + cy, colB.v, TextStyleGetAlpha_26dd30(self), 1.0f);
        i += 2;
        cx += adv;
    }
    GsPktClose_13f5b0(pk);
    FontResetScissor_26e340(self, pk);
    DrawListEndPrim_141a20(ctx);
}
