/* rgp:protos */
#define RGP_SELF_TextGridCellRectFill_208760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void TextGridCellRectFill_208760(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5, s64 arg6, s64 arg7, s32 arg_sp0) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;

    if (arg0 != 0 && TextGridCellRect_208650(&sp4C, &sp48, &sp44, &sp40, arg1, arg2, arg3, arg4, (int)(arg5), (int)(arg6), (int)(arg7)) != 0) {
        GsPktOpenPrim_13f730(arg0, 6);
        GsPktSetRGBAQVec_13edd0(arg0, arg_sp0);
        GsPktSetXYZf_13f060(arg0, (f32)sp4C, (f32)sp48, 1.0f);
        GsPktSetXYZf_13f060(arg0, (f32)sp44, (f32)sp40, 1.0f);
        GsPktClose_13f5b0(arg0);
    }
}
