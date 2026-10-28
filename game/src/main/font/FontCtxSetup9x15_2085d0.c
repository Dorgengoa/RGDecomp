/* rgp:protos */
#define RGP_SELF_FontCtxSetup9x15_2085d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void FontCtxSetup9x15_2085d0(s32 a, void *b)
{
    void *r;
    void *s;

    r = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(r, a, 1.0f);
    s = GetSysTextStyle_313570();
    TextStyleInit_26c610(s);
    TextStyleSetFontType_26edf0(s, b);
    TextStyleSetFixedCell_26f0e0(s, 9, 0xF);
}
