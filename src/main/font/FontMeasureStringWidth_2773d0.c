#include "types.h"

s32 FontFindCode_26ee00(s32, s8 *);
u8 FontGetCharWidth_26f4c0(s32, s32);
s32 strlen(s8 *);
s32 FontMapCharThunk_26ed60(s32, s32);
extern s32 D_0045F200[0x100];

s32 FontMeasureStringWidth_2773d0(s32 arg0, s8 *str)
{
    s32 len;
    s32 sum;
    s32 i;
    s16 w;
    s32 c;
    s8 *p;

    if (str == 0) {
        return -1;
    }
    sum = 0;
    len = strlen(str);
    i = 0;
    w = D_0045F200[0] - 1;
    while (i < len) {
        p = str + i;
        c = FontMapCharThunk_26ed60(arg0, *p);
        if (c == -2) {
            i++;
        } else if (c >= 0) {
            sum += FontGetCharWidth_26f4c0(arg0, c & 0xFFFF);
            i++;
        } else {
            if (FontFindCode_26ee00(arg0, p) <= 0) {
                i++;
            } else {
                sum += w;
                i += 2;
            }
        }
    }
    return sum;
}
