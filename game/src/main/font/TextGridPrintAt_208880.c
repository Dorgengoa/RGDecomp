/* rgp:protos */
#define RGP_SELF_TextGridPrintAt_208880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00208880 {
    u8 pad0[0x614];
    s32 unk614;
    s32 unk618;
    u8 pad61C[0x640 - 0x618 - 4];
    f32 unk640;
} S00208880;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void TextGridPrintAt_208880(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 *arg4, f32 fparg0)
{
    S00208880 *temp_2;

    if (arg4 == NULL || *arg4 == 0) {
        return;
    }
    temp_2 = ((S00208880 *)GetTextLayoutCtx_3133b0());
    temp_2->unk640 = fparg0;
    TextLayoutSetPos_3130d0(temp_2, arg0 + (arg2 * temp_2->unk614), arg1 + (arg3 * temp_2->unk618));
    TextLayoutPushStr_313090(temp_2, arg4);
    TextLayoutNop_313120();
    TextGridDrawGlyphMaybe_312da0(temp_2);
}
