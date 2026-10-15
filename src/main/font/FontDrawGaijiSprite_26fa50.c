#include "types.h"

typedef struct { f32 x; f32 y; f32 z; f32 w; } V4_26F;
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void TextQuadEmitRgba_26fb00(s32, V4_26F *, V4_26F *, s32);
extern s32 GaijiGetTex_270510(void);

void FontDrawGaijiSprite_26fa50(s32 arg0, V4_26F *arg1, V4_26F *arg2, s32 arg3)
{
    V4_26F a;
    V4_26F b;

    a = *arg1;
    b = *arg2;
    GsPktOpenPrim_13f730(arg0, 6);
    GsPktSetTexture_13ec00(arg0, GaijiGetTex_270510());
    TextQuadEmitRgba_26fb00(arg0, &a, &b, arg3);
    GsPktClose_13f5b0(arg0);
}
