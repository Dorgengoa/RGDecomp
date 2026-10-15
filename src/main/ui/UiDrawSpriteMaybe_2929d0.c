#include "types.h"

typedef struct Img {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10;
    f32 f14;
    s16 h18;
    s16 h1A;
    u16 h1C;
} Img;

typedef struct Spr {
    s32 x0;
    s32 x4;
} Spr;

extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZf_13f060(s32, f32, f32, f32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void UiSpriteApplyDrawFlags_293240(s32, Img *);
extern f32 D_0047D48C;

void UiDrawSpriteMaybe_2929d0(Spr *spr, s32 ctx, Img *img, s32 x, s32 y, f32 *rgba)
{
    s32 col[4];
    f32 fh;
    f32 nx;
    f32 ny;
    f32 hw;
    f32 hh;
    f32 ry;
    f32 t;
    f32 fw;
    f32 rx;
    s32 w;
    s32 h;
    s32 sx;
    s32 sy;
    s32 i;
    s32 j;
    u32 fl;
    s32 sa;
    s32 shadow;
    s32 dx;
    s32 dy;
    s32 ox;
    s32 oy;
    s32 px;
    s32 py;
    s32 ox2;
    s32 oy2;
    s32 j2;
    f32 ry2;
    f32 t2;
    s32 i2;
    f32 fh2;

    UiSpriteApplyDrawFlags_293240(ctx, img);
    GsPktOpenPrim_13f730(ctx, 6);
    GsPktSetTexture_13ec00(ctx, spr->x4);
    if (img->h4 <= 0) w = img->hC; else w = img->h4;
    if (img->h6 <= 0) h = img->hE; else h = img->h6;
    if (img->f10 <= 0.0f) nx = 1.0f; else nx = img->f10;
    if (img->f14 <= 0.0f) ny = 1.0f; else ny = img->f14;
    sx = img->h18;
    if (sx <= 0) {
        sx = w;
    }
    sy = img->h1A;
    if (sy <= 0) {
        sy = h;
    }
    for (i = 0; i < 4; i++) {
        col[i] = (s32)(128.0f * rgba[i]);
        if (col[i] < 0) {
            col[i] = 0;
        } else if (col[i] > 0xF0) {
            col[i] = 0xF0;
        }
    }
    fl = img->h1C;
    if (fl & 0x200) {
        if ((f32)col[3] > 0.0f) {
            col[3] = 0x26;
        }
    }
    if (fl & 8) {
        col[2] = 0x80;
        col[1] = 0x80;
        col[0] = 0x80;
    }
    sa = (s32)(D_0047D48C * rgba[3]);
    if ((f32)sa >= D_0047D48C) {
        sa = 0x33;
    }
    dx = 0;
    dy = 0;
    shadow = 0;
    if (fl & 0x40 | 0x80 | 0x100) {
        shadow = 1;
        if (fl & 0x40) {
            dx = 3;
            dy = 3;
        } else if (fl & 0x80) {
            dx = 6;
            dy = 5;
        } else if (fl & 0x100) {
            dx = 9;
            dy = 10;
        }
    }
    GsPktSetRGBAQ_13ee40(ctx, col[0], col[1], col[2], col[3]);
    if (img->h1C & 4) {
        oy = 0;
        for (j = 0; (f32)j < ny; j++) {
            ox = 0;
            fh = (f32)h;
            ry = ny - (f32)j;
            t = fh * ry;
            for (i = 0; (f32)i < nx; i++) {
                px = x + (img->h0 + ox);
                fw = (f32)w;
                rx = nx - (f32)i;
                py = y + (img->h2 + oy);
                if (rx < 1.0f) {
                    fw *= rx;
                }
                if (ry < 1.0f) {
                    fh = t;
                }
                hw = fw / 2.0f;
                hh = fh / 2.0f;
                if (shadow) {
                    GsPktSetRGBAQ_13ee40(ctx, 0, 0, 0, sa);
                    GsPktSetUV_13ed60(ctx, img->h8, img->hA);
                    GsPktSetXYZf_13f060(ctx, (f32)dx + ((f32)px - hw), (f32)dy + ((f32)py - hh), 0.0f);
                    GsPktSetUV_13ed60(ctx, img->h8 + img->hC, img->hA + img->hE);
                    GsPktSetXYZf_13f060(ctx, (f32)dx + ((f32)px + hw), (f32)dy + ((f32)py + hh), 0.0f);
                    GsPktSetRGBAQ_13ee40(ctx, col[0], col[1], col[2], col[3]);
                }
                GsPktSetUV_13ed60(ctx, img->h8, img->hA);
                GsPktSetXYZf_13f060(ctx, (f32)px - hw, (f32)py - hh, 0.0f);
                GsPktSetUV_13ed60(ctx, img->h8 + img->hC, img->hA + img->hE);
                GsPktSetXYZf_13f060(ctx, (f32)px + hw, (f32)py + hh, 0.0f);
                ox += sx;
            }
            oy += sy;
        }
    } else {
        oy2 = 0;
        for (j2 = 0; (f32)j2 < ny; j2++) {
            ox2 = 0;
            fh2 = (f32)h;
            ry2 = ny - (f32)j2;
            t2 = fh2 * ry2;
            for (i2 = 0; (f32)i2 < nx; i2++) {
                px = x + (img->h0 + ox2);
                fw = (f32)w;
                rx = nx - (f32)i2;
                py = y + (img->h2 + oy2);
                if (rx < 1.0f) {
                    fw *= rx;
                }
                if (ry2 < 1.0f) {
                    fh2 = t2;
                }
                if (shadow) {
                    GsPktSetRGBAQ_13ee40(ctx, 0, 0, 0, sa);
                    GsPktSetUV_13ed60(ctx, img->h8, img->hA);
                    GsPktSetXYZPixel_13f110(ctx, px + dx, py + dy, 0);
                    GsPktSetUV_13ed60(ctx, img->h8 + img->hC, img->hA + img->hE);
                    GsPktSetXYZf_13f060(ctx, (f32)dx + ((f32)px + fw), (f32)dy + ((f32)py + fh2), 0.0f);
                    GsPktSetRGBAQ_13ee40(ctx, col[0], col[1], col[2], col[3]);
                }
                GsPktSetUV_13ed60(ctx, img->h8, img->hA);
                GsPktSetXYZPixel_13f110(ctx, px, py, 0);
                GsPktSetUV_13ed60(ctx, img->h8 + img->hC, img->hA + img->hE);
                GsPktSetXYZf_13f060(ctx, (f32)px + fw, (f32)py + fh2, 0.0f);
                ox2 += sx;
            }
            oy2 += sy;
        }
    }
    GsPktClose_13f5b0(ctx);
}
