/* rgp:protos */
#define RGP_SELF_FontGetGlyphTable_26f6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern u8 D_004C0140[];
extern u8 D_004C1140[];
extern u8 D_004C2140[];

void *FontGetGlyphTable_26f6a0(s32 arg0, s32 *arg1)
{
    s32 v;
    void *var_16;

    v = ((signed char)TextStyleGetFontType_26ede0((void *)arg0));
    switch (v) {
    case 1:
        var_16 = D_004C0140;
        if (arg1 != NULL) {
            *arg1 = 0x1000;
        }
        break;
    case 0:
        var_16 = D_004C1140;
        if (arg1 != NULL) {
            *arg1 = 0x1000;
        }
        break;
    case 2:
        var_16 = D_004C2140;
        if (arg1 != NULL) {
            *arg1 = 0x1000;
        }
        break;
    }
    return var_16;
}
