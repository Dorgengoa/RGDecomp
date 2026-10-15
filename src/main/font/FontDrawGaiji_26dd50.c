#include "types.h"

typedef struct Rect {
    s32 a, b, c, d;
} Rect;

typedef struct Info {
    s16 m0;
    s16 m2;
    s16 m4;
    s16 m6;
    s8 m8;
    s8 m9;
    s8 mA;
} Info;

extern void GsPktSetTexture_13ec00(s32 arg0, s32 arg1);
extern s32 TextStyleGetFontType_26ede0(s32 arg0);
extern void FontGetLineAdvance_26f390(s32 arg0, s32 *arg1);
extern Info *FontFindGaijiMetric_26f8c0(s32, s32);
extern void TextQuadEmitRgba_26fb00(s32 arg0, Rect *arg1, Rect *arg2, s64 *arg3);
extern s32 GaijiGetTex_270510(void);

void FontDrawGaiji_26dd50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5)
{
    Info *p;

    p = FontFindGaijiMetric_26f8c0(arg0, arg2 & 0xFFFF);
    if (p != 0) {
        Rect r2;
        Rect r1;
        s32 e;
        s32 m2;
        s32 m4;
        s32 m6;
        s32 m8;
        s32 m9;
        s32 mA;

        m2 = p->m2;
        m4 = p->m4;
        m6 = p->m6;
        m9 = p->m9;
        m8 = p->m8;
        mA = p->mA;
        if (TextStyleGetFontType_26ede0(arg0) == 2) {
            mA++;
        }
        GsPktSetTexture_13ec00(arg1, GaijiGetTex_270510());
        FontGetLineAdvance_26f390(arg0, &e);
        r1.a = m4;
        r1.b = m2;
        r1.c = m8;
        r1.d = m6;
        r2.a = arg4 + mA + (e - m8) / 2;
        r2.b = arg3 + m9;
        r2.c = m8;
        r2.d = m6;
        TextQuadEmitRgba_26fb00(arg1, &r2, &r1, &arg5);
    }
}
