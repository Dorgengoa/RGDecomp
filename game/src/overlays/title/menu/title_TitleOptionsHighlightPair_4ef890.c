/* rgp:protos */
#define RGP_SELF_title_TitleOptionsHighlightPair_4ef890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EF890 -- four calls that all take the same
 * gp-relative handle plus one of the two incoming objects: a colour set to
 * white, a second colour set from one float broadcast over three channels,
 * then two identical layout calls that differ only in the 4th argument.
 *
 * `daddu $9, $7, $0` in the last call is the SAME constant 0x1A in two
 * argument slots, which is why the 4th call materialises it once.
 */

extern void *D_00484254;
extern f32 D_0047D288;

/*rgp*/
/*rgp*/

s32 title_TitleOptionsHighlightPair_4ef890(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    UiSetWidgetColor_2905b0(D_00484254, a, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetColor_2905b0(D_00484254, b, D_0047D288, D_0047D288, D_0047D288, 1.0f);
    UiSetSpriteUvRect_28f9d0(D_00484254, a, 0, 0, 0x48, 0x1A, 0);
    UiSetSpriteUvRect_28f9d0(D_00484254, b, 0, 0x1A, 0x48, 0x1A, 0);
    return 1;
}
