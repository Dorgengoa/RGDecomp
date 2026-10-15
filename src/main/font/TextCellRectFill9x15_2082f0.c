#include "types.h"

extern void GetSysTextStyle_313570(void);
extern void GsPktOpenPrim_13f730(void *, s32);
extern void GsPktSetRGBAQVec_13edd0(void *, s32);
extern void GsPktSetXYZf_13f060(void *, f32, f32, f32);
extern void GsPktClose_13f5b0(void *);

void TextCellRectFill9x15_2082f0(void *o, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                  s32 a7, s32 a8)
{
    if (o == 0) {
        return;
    }
    GetSysTextStyle_313570();
    GsPktOpenPrim_13f730(o, 6);
    GsPktSetRGBAQVec_13edd0(o, a8);
    GsPktSetXYZf_13f060(o, (f32)(a1 + a3 * 9 - a7 + 1),
                 (f32)(a2 + a4 * 15 - a7 + 3), 1.0f);
    GsPktSetXYZf_13f060(o, (f32)(a7 + (a1 + (a3 + a5) * 9) + 1),
                 (f32)(a7 + (a2 + (a4 + a6) * 15)), 1.0f);
    GsPktClose_13f5b0(o);
}
