/* rg-override: replaces game/src/main/ui/UiDrawWidgets_291910.cpp sha256 1fcd60254af159765dee54bdaa4dd0c9ec04e6c4d0f9e264584e4bf182ce1fa6
 * why: widescreen (docs/WIDESCREEN.md "Widget first frames (2026-11-09)", USER play-test 1105a, action gauge):
 * each widget's sprite list is drawn inside rg_layout_elem_begin / _end with the widget's extent
 * (its sprites' rectangles, UiDrawSpriteMaybe_2929d0's geometry), so a window that appears is
 * anchored as the whole window on its first frame instead of by its left corner piece (the
 * "Can't fight until the gauge refills!" box jumped 64 px left for one frame at 16:9).
 * Only widgets whose extent is centred (cluster rule); no-op at 4:3 (the layout hooks are
 * inactive).  RG_LAYOUT_WIDGET_EXTENT=0: off. */
/* rgp:protos */
#line 1
#include "types.h"

extern "C" {

typedef void (*DrawCb)(s32, void *, s32, s32, s32);

typedef struct Elem {
    u16 pad0;
    u16 parent;          /* 0x02 */
    u8 name[0x10];       /* 0x04 */
    f32 x;               /* 0x14 */
    f32 y;               /* 0x18 */
    s16 flags;           /* 0x1C */
    s16 pad1E;
    void *sprites;       /* 0x20 */
    void *prims;         /* 0x24 */
    void *texts;         /* 0x28 */
    DrawCb cb;           /* 0x2C */
    f32 color[4];        /* 0x30 */
} Elem;

typedef struct Node {
    Elem *elem;
    s32 pad4;
    struct Node *next;
} Node;

typedef struct Parent {
    u8 pad[0x14];
    f32 x;               /* 0x14 */
    f32 y;               /* 0x18 */
    u8 pad1C[0x14];
    f32 color[4];        /* 0x30 */
    u8 pad40[0x44];
    struct Parent *next; /* 0x84 */
} Parent;

typedef struct Sprite {
    s16 id;
    u8 pad2[0x1A];
    u16 flags;           /* 0x1C */
    u8 pad1E[2];
} Sprite;

typedef struct Prim {
    s16 id;
    u8 pad2[0x18];
    s16 flags;           /* 0x1A */
    u8 pad1C[4];
} Prim;

typedef struct Text {
    s16 x;
    s16 y;
    s32 str;
    u16 attr;
    s8 font;             /* 0x0A */
    u8 padB;
    s32 msg;             /* 0x0C */
} Text;

typedef struct TextPos {
    s16 x;
    s16 y;
    s32 str;
    u16 attr;
    u8 padA[6];
} TextPos;

typedef struct Ctx {
    Node *list;
    s16 *cur;            /* 0x04 */
    s32 key;             /* 0x08 */
    s32 padC;
    s16 active;          /* 0x10 */
} Ctx;

s32 GetDrawCtx_15de80(void);
s32 GetDrawCtxNameTable_15de40(void);
Parent *UiFindWidget_290460(Ctx *, u16);
s16 *NameTableFindByName_159fb0(s32, u8 *, s32);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
s32 DrawListBeginPrim_141b00(s32);
void DrawListEndPrim_141a20(s32);
void GsPktSetupUiDrawState_2932b0(s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void UiDrawSpriteMaybe_2929d0(Ctx *, s32, Sprite *, s32, s32, f32 *);
void UiDrawSpritePixelMaybe_292300(Ctx *, s32, Prim *, s32, s32, f32 *);
void TextStyleInitWithFontType_2931c0(void *, long long);
void UiTextElemInit_2931a0(TextPos *);
void FontMeasureString_26daf0(void *, s32, s32 *, s32 *);
void TextStyleSetRgbaU32_26f210(void *, s32);
void UiDrawWidgetText_2921f0(Ctx *, s32, TextPos *, s32, s32, f32 *);
extern u8 D_004DB150[];
/* rg-override: widescreen element extent (src/settings/rg_layout.h) */
void rg_layout_elem_begin(float x0_px, float x1_px);
void rg_layout_elem_end(void);
int rg_layout_active(void);
int rg_layout_cluster_anchor(float x0, float x1, float left, float width);
}
#include <stdlib.h>
extern "C" {
typedef struct RgImg {
    s16 h0, h2, h4, h6, h8, hA, hC, hE;
    f32 f10, f14;
    s16 h18, h1A;
    u16 h1C;
} RgImg;
/* the horizontal extent (screen pixels) of a sprite list as UiDrawSpriteMaybe_2929d0 draws it at x */
static int rg_widget_extent(const Sprite *spr, s32 x, f32 *x0, f32 *x1)
{
    static int on = -1;
    int any = 0;
    if (on < 0) { const char *e = getenv("RG_LAYOUT_WIDGET_EXTENT"); on = !(e && e[0] == '0'); }
    if (!on || !rg_layout_active()) return 0;
    for (; spr->id != -1; spr++) {
        const RgImg *img = (const RgImg *)spr;
        s32 w = img->h4 <= 0 ? img->hC : img->h4, sx = img->h18 <= 0 ? w : img->h18;
        f32 nx = img->f10 <= 0.0f ? 1.0f : img->f10, a, b, last = 0.0f;
        s32 i;
        for (i = 1; (f32)i < nx; i++) last = (f32)(i * sx);
        if (img->h1C & 4) { a = (f32)(x + img->h0) - 0.5f * (f32)w; b = (f32)(x + img->h0) + last + 0.5f * (f32)w; }
        else { a = (f32)(x + img->h0); b = a + last + (f32)w; }
        if (!any || a < *x0) *x0 = a;
        if (!any || b > *x1) *x1 = b;
        any = 1;
    }
    /* only a centred widget nearly as wide as the screen (a message window); the party HUD's
     * widgets (a panel's pieces, the 0..397 rule over the row) keep their pieces' own rectangles:
     * widened, they changed what the HUD's first frame inherits */
    return any && *x1 - *x0 >= 0.85f * 512.0f && rg_layout_cluster_anchor(*x0, *x1, 0.0f, 512.0f) == 2 /* RG_ANCHOR_CENTER */;
}

void UiDrawWidgets_291910(Ctx *ctx) {
    s32 db;
    s32 lastId;
    bool drawText;
    s32 w;
    s32 h;
    s32 w2;
    s32 h2;
    f32 col[4] __attribute__((aligned(16)));
    f32 mul[4] __attribute__((aligned(16)));
    TextPos tp __attribute__((aligned(16)));
    TextPos tp2 __attribute__((aligned(16)));
    s32 gfx;
    Node *node;
    Elem *e;
    bool ok;
    s32 x;
    s32 y;
    s32 i;
    Parent *p;
    Sprite *spr;
    Prim *prim;
    Text *txt;
    s32 ctxHandle;

    gfx = GetDrawCtx_15de80();
    db = GetDrawCtxNameTable_15de40();
    lastId = -1;
    drawText = 0;
    node = ctx->list;
    while (node != 0) {
        e = node->elem;
        if (e == 0) break;
        if (e->flags & 1) { node = node->next; continue; }
        if (e->color[3] <= 0.0f) { node = node->next; continue; }
        ok = 1;
        x = (s32)e->x;
        y = (s32)e->y;
        for (i = 0; i < 4; i++) {
            col[i] = e->color[i];
            mul[i] = 1.0f;
        }
        if (e->parent != 0) {
            for (p = UiFindWidget_290460(ctx, e->parent); p != 0; p = p->next) {
                x = (s32)((f32)x + p->x);
                y = (s32)((f32)y + p->y);
                for (i = 0; i < 4; i++) {
                    mul[i] = mul[i] * p->color[i];
                    col[i] = col[i] * p->color[i];
                }
                if (col[3] <= 0.0f) {
                    ok = 0;
                    break;
                }
            }
        }
        if (col[3] <= 0.0f) goto next;
        if (!ok) goto next;
        if ((ctx->cur = NameTableFindByName_159fb0(db, e->name, ctx->key)) == 0) {
            ctx->cur = NameTableFindByName_159fb0(db, e->name, -1);
        }
        if (ctx->cur != 0 && lastId != *ctx->cur) {
            DrawListAddTexLoad_1418c0(gfx, *ctx->cur, 0.0f);
            lastId = *ctx->cur;
        }
        spr = (Sprite *)e->sprites;
        if (e->flags & 0x800) {
            if (e->cb != 0) e->cb(0, spr, x, y, 1);
            if (e->cb != 0) e->cb(0, spr, x, y, 0);
            ctxHandle = DrawListBeginPrim_141b00(gfx);
        } else {
            ctxHandle = DrawListBeginPrim_141b00(gfx);
            if (spr != 0) {
                if (e->cb != 0) e->cb(ctxHandle, spr, x, y, 1);
                GsPktSetupUiDrawState_2932b0(ctxHandle);
                {
                    f32 ex0, ex1;
                    if (rg_widget_extent(spr, x, &ex0, &ex1)) rg_layout_elem_begin(ex0, ex1);
                }
                for (; spr->id != -1; spr++) {
                    if (spr->flags & 0x10) {
                        UiDrawSpriteMaybe_2929d0(ctx, ctxHandle, spr, x, y, e->color);
                    } else if (spr->flags & 0x20) {
                        UiDrawSpriteMaybe_2929d0(ctx, ctxHandle, spr, x, y, mul);
                    } else {
                        UiDrawSpriteMaybe_2929d0(ctx, ctxHandle, spr, x, y, col);
                    }
                }
                rg_layout_elem_end();
                if (e->cb != 0) e->cb(ctxHandle, spr, x, y, 0);
            }
        }
        prim = (Prim *)e->prims;
        if (prim != 0) {
            if (!(e->flags & 0x800)) {
                if (e->cb != 0) e->cb(ctxHandle, spr, x, y, 1);
            }
            GsPktSetupUiDrawState_2932b0(ctxHandle);
            GsPktSetZWriteMask_13e430(ctxHandle, 0);
            for (; prim->id != -1; prim++) {
                if (e->flags & 0x800) continue;
                if (prim->flags & 0x80) {
                    UiDrawSpritePixelMaybe_292300(ctx, ctxHandle, prim, x, y, e->color);
                } else if (prim->flags & 0x100) {
                    UiDrawSpritePixelMaybe_292300(ctx, ctxHandle, prim, x, y, mul);
                } else {
                    UiDrawSpritePixelMaybe_292300(ctx, ctxHandle, prim, x, y, col);
                }
            }
            if (!(e->flags & 0x800)) {
                if (e->cb != 0) e->cb(ctxHandle, spr, x, y, 0);
            }
        }
        DrawListEndPrim_141a20(gfx);
        txt = (Text *)e->texts;
        if (txt == 0) goto next;
        if (e->flags & 0x400) {
            DrawListAddTexLoad_1418c0(gfx, 0x338, 1.0f);
            lastId = 0x338;
            TextStyleInitWithFontType_2931c0(D_004DB150, (long long)(txt->font));
            if (e->cb != 0) e->cb(0, spr, x, y, 1);
            for (; txt->x != -1; txt++) {
                UiTextElemInit_2931a0(&tp);
                tp.x = txt->x;
                tp.y = txt->y;
                tp.str = txt->str;
                tp.attr = txt->attr;
                if (e->flags & 0x1000) {
                    FontMeasureString_26daf0(D_004DB150, tp.str, &w, &h);
                    tp.x = txt->x - (w >> 1);
                }
                TextStyleSetRgbaU32_26f210(D_004DB150, txt->msg);
                UiDrawWidgetText_2921f0(ctx, 0, &tp, x, y, col);
            }
            if (e->cb != 0) e->cb(0, spr, x, y, 0);
        } else {
            drawText = 1;
        }
    next:
        node = node->next;
    }
    node = ctx->list;
    if (!drawText || ctx->active == 0) return;
    DrawListAddTexLoad_1418c0(gfx, 0x338, 1.0f);
    while (node != 0) {
        e = node->elem;
        if (e == 0) return;
        if (e->flags & 1) { node = node->next; continue; }
        if (e->texts == 0 || e->color[3] <= 0.0f) { node = node->next; continue; }
        x = (s32)e->x;
        y = (s32)e->y;
        for (i = 0; i < 4; i++) {
            col[i] = e->color[i];
        }
        if (e->parent != 0) {
            for (p = UiFindWidget_290460(ctx, e->parent); p != 0; p = p->next) {
                x = (s32)((f32)x + p->x);
                y = (s32)((f32)y + p->y);
                for (i = 0; i < 4; i++) {
                    col[i] = col[i] * p->color[i];
                }
            }
        }
        if (col[3] <= 0.0f) goto next2;
        if (e->flags & 0x400) goto next2;
        txt = (Text *)e->texts;
        TextStyleInitWithFontType_2931c0(D_004DB150, (long long)(txt->font));
        if (e->cb != 0) e->cb(0, spr, x, y, 1);
        for (; txt->x != -1; txt++) {
            UiTextElemInit_2931a0(&tp2);
            tp2.x = txt->x;
            tp2.y = txt->y;
            tp2.attr = txt->attr;
            tp2.str = txt->str;
            if (e->flags & 0x1000) {
                FontMeasureString_26daf0(D_004DB150, tp2.str, &w2, &h2);
                tp2.x = txt->x - (w2 >> 1);
            }
            TextStyleSetRgbaU32_26f210(D_004DB150, txt->msg);
            UiDrawWidgetText_2921f0(ctx, 0, &tp2, x, y, col);
        }
        if (e->cb != 0) e->cb(0, spr, x, y, 0);
    next2:
        node = node->next;
    }
}

}
