/* rgp:protos */
#define RGP_SELF_FontDrawTextAtCell_208490 1
#define RGP_SELF_TextStyleSetGradRgbaQuad_26f1b0 1
#define RGP_SELF_TextStyleSetRgbaQuad_26f250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u64 v; } C8;

/*rgp*/
/*rgp*/
/*rgp*/
extern void TextStyleSetGradRgbaQuad_26f1b0(s32, C8);
/*rgp*/
/*rgp*/
extern void TextStyleSetRgbaQuad_26f250(s32, C8);
/*rgp*/
/*rgp*/
/*rgp*/

void FontDrawTextAtCell_208490(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 *arg4, f32 fparg0)
{
    C8 sp98 __attribute__((aligned(16)));
    C8 sp90 __attribute__((aligned(16)));
    C8 sp88 __attribute__((aligned(16)));
    C8 sp80 __attribute__((aligned(16)));
    s32 temp_2;

    if (arg4 == NULL || *arg4 == 0) {
        return;
    }
    GetDrawCtx_15de80();
    temp_2 = ((s32)GetSysTextStyle_313570());
    TextStyleGetRgba_26f2a0(&sp88, temp_2);
    sp98 = sp88;
    TextStyleGetGradRgba_26f200(&sp80, temp_2);
    sp90 = sp80;
    TextStyleSetRgba_26f280(temp_2, 0x80, 0x80, 0x80, 0x80);
    TextStyleSetGradRgba_26f1e0(temp_2, 0x80, 0x80, 0x80, 0x80);
    TextStyleSetAlpha_26dd40(temp_2, (s32)fparg0);
    FontDrawText_26cdc0(temp_2, arg4, arg0 + (arg2 * 9), arg1 + (arg3 * 0xF));
    TextStyleSetRgbaQuad_26f250(temp_2, sp98);
    TextStyleSetGradRgbaQuad_26f1b0(temp_2, sp90);
}
