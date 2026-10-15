/* PARKED s15i: string/lookup-table encoder with dense 64-bit sign-extension
 * arithmetic on s16 array elements spaced 0x40 bytes apart (`var_19 += 0x20`
 * on a s16* -- i.e. a 0x40-byte stride struct) and multiple interacting
 * counters; 0 round trips spent -- the m2c draft's control flow (particularly
 * the short-circuit `||` on line with IsSjisLeadByte_370f60) needs to be worked out
 * by hand from asm/matchings/main/UiLayoutStringGlyphs_28a800.s before writing C. Left
 * untouched rather than guess wrong on a load-bearing string-table function. */
/* s49m: len(ed=15,d=1) */
#include "types.h"

typedef struct Glyph {
    s16 x;
    s16 pad2;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 w2;
    s16 h2;
    u8 pad10[0x10];
} Glyph;

extern u8 IsSjisLeadByte_370f60(s8);
extern u8 *UiGlyphFind_206ea0(s32);

void UiLayoutStringGlyphs_28a800(Glyph *out, s8 *str, s16 center, s16 x, s16 spacing)
{
    Glyph *g;
    s8 *s;
    s32 cx;
    s32 c;
    u16 lo;
    u8 *info;
    s16 half;
    s16 v;

    s32 w;
    s32 code;
    u8 t;
    if (out == NULL) {
        return;
    }
    g = out;
    s = str;
    cx = x;
    while (*s != 0) {
        c = (u16)(s8)*s;
        s++;
        t = IsSjisLeadByte_370f60((s8)c);
        code = (u16)c;
        if (t != 0) {
            lo = *s;
            s++;
            code = (u16)((code << 8) | lo);
            if (lo == 0) {
                break;
            }
        }
        info = UiGlyphFind_206ea0(code);
        w = info[3];
        g->w2 = w;
        g->w = w;
        g->h2 = 0x16;
        g->h = 0x16;
        if (cx == -1) {
            cx++;
        }
        g->x = cx;
        cx += w + spacing;
        g->u = info[4];
        g->v = info[5];
        g++;
    }
    g->x = -1;
    if (center == 1) {
        half = (cx - x) / 2;
        for (; *str != 0; str++) {
            v = out->x - half;
            out->x = v;
            if (v == -1) {
                out->x = 0;
            }
            out++;
        }
    }
}
