/* rgp:protos */
#define RGP_SELF_FontDrawGaijiSprite_26fa50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x; f32 y; f32 z; f32 w; } V4_26F;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void FontDrawGaijiSprite_26fa50(s32 arg0, V4_26F *arg1, V4_26F *arg2, s32 arg3)
{
    V4_26F a __attribute__((aligned(16)));
    V4_26F b __attribute__((aligned(16)));

    a = *arg1;
    b = *arg2;
    GsPktOpenPrim_13f730(arg0, 6);
    GsPktSetTexture_13ec00(arg0, GaijiGetTex_270510());
    TextQuadEmitRgba_26fb00(arg0, &a, &b, arg3);
    GsPktClose_13f5b0(arg0);
}
