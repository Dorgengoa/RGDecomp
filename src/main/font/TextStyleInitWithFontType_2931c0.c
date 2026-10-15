#include "types.h"

extern void TextStyleInit_26c610(void);
extern void TextStyleSetFontType_26edf0(s32, s64);
extern void TextStyleAddSpacing_26f2b0(s32, s32, s32);

void TextStyleInitWithFontType_2931c0(s32 arg0, s64 arg1) {
    s64 temp_16;

    TextStyleInit_26c610();
    temp_16 = (s64)(s8)arg1;
    TextStyleSetFontType_26edf0(arg0, temp_16);
    if (temp_16 == 2) {
        TextStyleAddSpacing_26f2b0(arg0, 3, 0);
        return;
    }
    if (temp_16 == 1) {
        TextStyleAddSpacing_26f2b0(arg0, 3, 0);
    }
}
