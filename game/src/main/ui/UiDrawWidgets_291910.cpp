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
                for (; spr->id != -1; spr++) {
                    if (spr->flags & 0x10) {
                        UiDrawSpriteMaybe_2929d0(ctx, ctxHandle, spr, x, y, e->color);
                    } else if (spr->flags & 0x20) {
                        UiDrawSpriteMaybe_2929d0(ctx, ctxHandle, spr, x, y, mul);
                    } else {
                        UiDrawSpriteMaybe_2929d0(ctx, ctxHandle, spr, x, y, col);
                    }
                }
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
