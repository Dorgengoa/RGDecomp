#pragma opt_repositioncode on
#include "types.h"

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

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

extern s32 FontGetGlyphPage_26e240(void *, s32);
extern void GsPktSetTexture_13ec00(void *, s32);
extern void FontGetGlyphRect_26e040(V4 *, void *, s32);
extern void FontIsAsciiCode_26ed80(void *, s32);
extern void RectScaleKeepBottom_26f940(R4 *, f32);
extern void FontDrawGlyphOutline_26e450(void *, void *, R4 *, V4 *, s32);
extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern s32 TextStyleGetZEnable_26e410(void *);
extern s32 TextStyleGetZ_26e430(void *);
extern void GsPktSpriteUVRect_26eb30(void *, R4 *, V4 *, s32);

void FontDrawGlyph_26de80(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5, u8 arg6, f32 f)
{
    V4 vd;
    R4 rc;
    V4 vb;
    s32 t;
    u16 id;
    s32 al;
    u8 alpha;

    alpha = ((u8 *)&arg5)[3];
    id = arg2;
    if (id == 0xFF00) {
        return;
    }
    if (id != 0xFF01) {
        goto body;
    }
    return;
body:
    t = FontGetGlyphPage_26e240(arg0, arg2);
    if (t == 0) {
        return;
    }
    GsPktSetTexture_13ec00(arg1, t);
    FontGetGlyphRect_26e040(&vb, arg0, arg2);
    *(V4 *)&vd = vb;
    FontIsAsciiCode_26ed80(arg0, id);
    rc.a = arg3;
    rc.c = ((R4 *)&vd)->c;
    rc.d = ((R4 *)&vd)->d;
    rc.b = arg4;
    RectScaleKeepBottom_26f940(&rc, f);
    al = arg6;
    FontDrawGlyphOutline_26e450(arg0, arg1, &rc, &vd, al);
    GsPktSetRGBAQ_13ee40(arg1, ((u8 *)&arg5)[0], ((u8 *)&arg5)[1], ((u8 *)&arg5)[2], (u8)(al * alpha / 128));
    if (TextStyleGetZEnable_26e410(arg0) != 0) {
        GsPktSpriteUVRect_26eb30(arg1, &rc, &vd, TextStyleGetZ_26e430(arg0));
        return;
    }
    GsPktSpriteUVRect_26eb30(arg1, &rc, &vd, 0);
}
