/* rgp:protos */
#define RGP_SELF_FontWrapText_26d5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Glyph {
    u8 pad0[4];
    s16 len;
    u16 code;
} Glyph;

typedef struct Metric {
    u8 pad0[6];
    s16 adv;
    u8 pad8;
    s8 bearing;
} Metric;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void strncpy(s8 *, s8 *, s32);

s32 FontWrapText_26d5a0(s32 font, s8 *src, s8 *dst, s32 maxW, s32 maxH, s32 *out) {
    u16 code;
    s32 w;
    s32 h;
    s32 len;
    Metric *m;
    Glyph *g;
    s32 adv;
    s32 n;
    s32 ok;
    s32 count;
    s32 x;
    s32 y;

    if (src == 0 || dst == 0 || maxW == 0) {
        return 0;
    }
    count = 0;
    x = 0;
    y = 0;
    ok = 1;
    while (*src != 0) {
        FontGetCharCellSize_26f310(font, &w, &h, FontMapAsciiChar_26f530((long long)(*src)));
        if (*src == 0x20 && maxW < x + (w + FontMeasureWordWidth_26d8d0(font, src + 1))) {
            src++;
            *dst = 0x0A;
            count++;
            dst++;
            x = 0;
            y += h;
            if (maxH != 0 && maxH < y + (u8)FontGetLineHeight_26f3e0(font)) {
                ok = 0;
                break;
            }
            if (*src == 0x0A) {
                src++;
            }
            if (*src == 0x5C && src[1] == 0x6E) {
                src += 2;
            }
        } else if (*src == 0x0A) {
            *dst = *src;
            src++;
            dst++;
            count++;
            x = 0;
            y += h;
            if (maxH != 0 && maxH < y + (u8)FontGetLineHeight_26f3e0(font)) {
                ok = 0;
                break;
            }
        } else if (*src == 0x5C && src[1] == 0x6E) {
            *dst = 0x0A;
            src += 2;
            dst++;
            count++;
            x = 0;
            y += h;
            if (maxH != 0 && maxH < y + (u8)FontGetLineHeight_26f3e0(font)) {
                ok = 0;
                break;
            }
        } else {
            if (FontMatchSymbolTag_26ef40(src, &code, &len) != 0) {
                strncpy(dst, src, len);
                src += len;
                dst += len;
                count += len;
                FontGetCharCellSize_26f310(font, &w, &h, code);
                x += w;
            } else if ((g = ((Glyph *)TextGaijiTagFind_26f060(src))) != 0 && (m = ((Metric *)FontFindGaijiMetric_26f8c0(font, g->code)), g != 0)) {
                n = g->len;
                strncpy(dst, src, n);
                src += n;
                dst += n;
                count += n;
                x += m->bearing + m->adv;
            } else {
                count++;
                *dst = *src;
                src++;
                dst++;
                x += w;
            }
        }
    }
    *dst = 0;
    if (out != 0) {
        *out = ok;
    }
    return count + 1;
}
