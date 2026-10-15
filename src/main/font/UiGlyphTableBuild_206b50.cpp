#include "types.h"

extern "C" {

typedef struct Glyph {
    u16 code;
    u8 idx;
    u8 w;
    u8 x;
    u8 y;
} Glyph;

extern Glyph *MemStackNew_14e1b0(s32, s32);
extern s32 StrParseIntField_206d80(s32, s32 *);
extern s32 IsSjisLeadByte_370f60(s8);
extern void *memcpy(void *, const void *, u32);

extern s32 D_00481B88;
extern Glyph *D_00481B8C;

}
extern "C" void UiGlyphTableBuild_206b50(s32 arg0, s8 *str, s32 arg2) {
    s8 *p;
    s8 c;
    Glyph *g;
    s32 i;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 lim;
    u16 code;
    u16 lo;
    u16 k;
    s32 r;
    bool swapped;
    Glyph *a;
    Glyph *b;
    Glyph tmp;
    s32 st;
    s32 cur;

    D_00481B88 = 0;
    p = str;
    while ((c = *p) != 0) {
        p++;
        if (IsSjisLeadByte_370f60(c) & 0xFF) {
            if (*p++ == 0) {
                break;
            }
        }
        D_00481B88++;
    }
    D_00481B8C = MemStackNew_14e1b0(D_00481B88 * 6, arg0);
    st = 0;
    w = StrParseIntField_206d80(arg2, &st);
    h = StrParseIntField_206d80(st, &st);
    lim = StrParseIntField_206d80(st, &st);
    cur = st;
    i = 0;
    g = D_00481B8C;
    x = 0;
    y = 0;
    while ((c = *str) != 0) {
        str++;
        k = c;
        r = IsSjisLeadByte_370f60(k);
        code = k;
        if (r & 0xFF) {
            lo = *str;
            str++;
            code = (code << 8) | lo;
            if (lo == 0) {
                break;
            }
        }
        g->code = code;
        g->x = x;
        g->y = y;
        g->w = StrParseIntField_206d80(cur, &st);
        cur = st;
        x += w;
        if (lim <= x + w) {
            y += h;
            x = 0;
        }
        g->idx = i;
        g++;
        i++;
    }
    do {
        swapped = false;
        a = D_00481B8C;
        for (i = 1, b = a + 1; i < D_00481B88; i++, a++, b++) {
            if (a->code > b->code) {
                memcpy(&tmp, a, 6);
                memcpy(a, b, 6);
                memcpy(b, &tmp, 6);
                swapped = true;
            }
        }
    } while (swapped);
}
