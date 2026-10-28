/* rgp:protos */
#define RGP_SELF_FontSystemLoad_3133c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Retail FALLS THROUGH into the `b <epilogue>` that returns 0, so the source
   guard is `if (b == 0) return 0;`.  Four callee-saved values: params a,b,c
   then the local h => $19,$18,$17,$16 (declaration order, descending). */

extern u8 D_004E7B40[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 FontSystemLoad_3133c0(void *a, void *b, void *c)
{
    void *h;

    if (b == 0) {
        return 0;
    }
    h = GetSysTextStyle_313570();
    MemStackReset_14d830(D_004E7B40);
    TextStyleInit_26c610(h);
    MesFontLoad_270040(a, D_004E7B40, b, c);
    GaijiLoadImage_2705a0(b);
    GaijiRegister_270520(c);
    TextStyleInitPreset_26c540(h, 0);
    return 1;
}
