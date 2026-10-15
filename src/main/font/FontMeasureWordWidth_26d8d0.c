#include "types.h"

typedef struct Q {
    u8 pad0[4];
    s16 x4;
    u16 x6;
} Q;

typedef struct R {
    u8 pad0[6];
    s16 x6;
    u8 pad8;
    s8 x9;
} R;

extern s32 FontMatchSymbolTag_26ef40(s8 *, u16 *, s32 *);
extern Q *TextGaijiTagFind_26f060(s8 *);
extern void FontGetCharCellSize_26f310(s32, s32 *, s32 *, u16);
extern s32 FontMapAsciiChar_26f530(s32);
extern R *FontFindGaijiMetric_26f8c0(s32, u16);

s32 FontMeasureWordWidth_26d8d0(s32 arg0, s8 *arg1)
{
    u16 code;
    s32 len;
    s32 w1;
    s32 h1;
    s32 w2;
    s32 h2;
    s8 *p;
    s32 n;
    s32 c;
    Q *q;
    R *r;

    if (arg1 == 0) {
        return 0;
    }
    p = arg1;
    n = 0;
    while (*p != 0) {
        c = FontMapAsciiChar_26f530(*p);
        if (c == 0 || c == -2 || c == -1) {
            break;
        }
        if (p[0] == 0x5C && p[1] == 0x6E) {
            break;
        }
        if (FontMatchSymbolTag_26ef40(p, &code, &len) != 0) {
            FontGetCharCellSize_26f310(arg0, &w1, &h1, code);
            n += w1;
            p += len;
            continue;
        }
        q = TextGaijiTagFind_26f060(p);
        if (q != 0) {
            r = FontFindGaijiMetric_26f8c0(arg0, q->x6);
            if (q != 0) {
                p += q->x4;
                n += r->x9 + r->x6;
                continue;
            }
        }
        FontGetCharCellSize_26f310(arg0, &w2, &h2, c);
        n += w2;
        p++;
    }
    return n;
}
