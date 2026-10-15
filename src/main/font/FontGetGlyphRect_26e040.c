#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Rect;

extern s32 TextStyleGetFontType_26ede0(s32);
extern s32 FontGetGlyphBankType1_26f7d0(s32);
extern s32 FontIsAsciiCodeNoFont_26f830(s32);

Rect FontGetGlyphRect_26e040(s32 arg1, s32 arg2) {
    Rect r;
    s32 bank;
    s32 k;
    s32 t;

    bank = 0;
    k = (u16)arg2;
    if (FontIsAsciiCodeNoFont_26f830(k) == 0) {
        bank = FontGetGlyphBankType1_26f7d0(arg2);
    }
    if (bank >= 0) {
        switch (TextStyleGetFontType_26ede0(arg1)) {
        case 1:
            t = k - bank * 0x1DC;
            r.unk0 = (t % 28) * 18;
            r.unk4 = (t / 28) * 22;
            r.unk8 = 18;
            r.unkC = 22;
            break;
        case 0:
            t = k - bank * 0x2A0;
            r.unk0 = (t % 32) * 16;
            r.unk4 = (t / 32) * 18;
            r.unk8 = 16;
            r.unkC = 18;
            break;
        case 2:
            t = k - bank * 0x260;
            r.unk0 = (t % 32) * 16;
            r.unk4 = (t / 32) * 20;
            r.unk8 = 16;
            r.unkC = 20;
            break;
        }
    }
    return r;
}
