#include "types.h"

extern s32 TextStyleGetFontType_26ede0(void);
extern u8 D_004C0140[];
extern u8 D_004C1140[];
extern u8 D_004C2140[];

void *FontGetGlyphTable_26f6a0(s32 arg0, s32 *arg1)
{
    s32 v;
    void *var_16;

    v = TextStyleGetFontType_26ede0();
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
