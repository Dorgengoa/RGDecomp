/* rgp:protos */
#define RGP_SELF_PadLostMsgDrawMaybe_2f5e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN PadLostMsgDrawMaybe_2f5e90 -- builds a text object, measures it and centres it.
   The `bnel $18,$0` past `addiu $4,$0,0x2F` is an `if` whose body is
   the FALL-THROUGH arm, so the source tests `== 0`.
   The 0x88 out-parameter is written and never read. */

typedef struct Txt5e90 {
    u8 d[0x48];
} Txt5e90;

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

void PadLostMsgDrawMaybe_2f5e90(s32 a, s32 b)
{
    Txt5e90 t __attribute__((aligned(16)));
    void *w;
    void *s;
    s32 id;
    s32 px;
    s32 py;
    s32 cx;
    s32 cy;

    w = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(w, 0x338, 1.0f);
    TextStyleInit_26c610(&t);
    TextStyleInit_26c610(&t);
    TextStyleSetFontType_26edf0(&t, 1);
    TextStyleAddSpacing_26f2b0(&t, 3, 0);
    TextStyleSetRgbaU32_26f210(&t, 0x80686A6B);
    TextStyleSetGradRgbaU32_26f170(&t, 0x80686A6B);
    if (a == 0) {
        id = 0x2F;
    } else {
        id = 0x30;
    }
    s = MsgGetTextByIndex_279040(id);
    cx = 0;
    cy = 0;
    FontMeasureString_26daf0(&t, s, &cx, &cy);
    /* `cx` is ADDRESS-TAKEN, so re-using it for the halved result stores
       and re-loads it; the halved value gets its own local. */
    px = (DrawEnvGetWidth_1451e0(w) - cx) >> 1;
    py = (DrawEnvGetHeight_1451d0(w) - 0x18) >> 1;
    FontDrawText_26cdc0(&t, s, px, py + b);
}
