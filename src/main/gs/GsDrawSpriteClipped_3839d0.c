#include "types.h"

typedef struct Rect {
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
} Rect;

extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQVec_13edd0(s32, s32);
extern void GsPktSetXYZf_13f060(s32, f32, f32, f32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);

void GsDrawSpriteClipped_3839d0(s32 ctx, Rect *r, Rect *uv, s32 tex)
{
    s32 scr;
    f32 w;
    f32 h;
    f32 t;

    scr = GetDrawCtx_15de80();
    w = (f32)DrawEnvGetWidth_1451e0(scr);
    h = (f32)DrawEnvGetHeight_1451d0(scr);
    if (!(r->x0 < r->x1)) {
        return;
    }
    if (!(r->y0 < r->y1)) {
        return;
    }
    if (r->x1 < 0.0f) {
        return;
    }
    if (r->y1 < 0.0f) {
        return;
    }
    if (!(r->x0 <= w)) {
        return;
    }
    if (!(r->y0 <= h)) {
        return;
    }
    if (r->x0 < 0.0f) {
        t = -r->x0 / (r->x1 - r->x0);
        uv->x0 = uv->x0 + t * (uv->x1 - uv->x0);
        r->x0 = 0.0f;
    }
    if (r->y0 < 0.0f) {
        t = -r->y0 / (r->y1 - r->y0);
        uv->y0 = uv->y0 + t * (uv->y1 - uv->y0);
        r->y0 = 0.0f;
    }
    if (!(r->x1 <= w)) {
        uv->x1 = uv->x0 + (uv->x1 - uv->x0) * ((w - r->x0) / (r->x1 - r->x0));
        r->x1 = w;
    }
    if (!(r->y1 <= h)) {
        uv->y1 = uv->y0 + (uv->y1 - uv->y0) * ((h - r->y0) / (r->y1 - r->y0));
        r->y1 = h;
    }
    GsPktSetRGBAQVec_13edd0(ctx, tex);
    GsPktSetUV_13ed60(ctx, (s32)uv->x0, (s32)uv->y0);
    GsPktSetXYZf_13f060(ctx, r->x0, r->y0, 0.0f);
    GsPktSetUV_13ed60(ctx, (s32)uv->x1, (s32)uv->y1);
    GsPktSetXYZf_13f060(ctx, r->x1, r->y1, 0.0f);
}
