/* rg-override: replaces game/src/main/font/FontGetGlyphRect_26e040.c sha256 5c10976b7d2783643f34b9aa1454a1e944b6454ea79a1dc28670bd6be53a6198
 * why: struct return (docs/LINUX.md "Struct returns", tools/linux/sretfix.py): callers use the MIPS hidden-pointer view; on Linux the definition keeps the MSVC caller-pops convention */
/* rgp:protos */
#define RGP_SELF_FontGetGlyphRect_26e040 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Rect;

/*rgp*/
/*rgp*/
/*rgp*/

#ifndef _WIN32   /* rg-sret */
#define FontGetGlyphRect_26e040 FontGetGlyphRect_26e040_sret
#endif
Rect FontGetGlyphRect_26e040(s32 arg1, s32 arg2) {
    Rect r __attribute__((aligned(16)));
    s32 bank;
    s32 k;
    s32 t;

    bank = 0;
    k = (u16)arg2;
    if (FontIsAsciiCodeNoFont_26f830(k) == 0) {
        bank = FontGetGlyphBankType1_26f7d0(arg2);
    }
    if (bank >= 0) {
        switch (((signed char)TextStyleGetFontType_26ede0(arg1))) {
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

#ifndef _WIN32   /* rg-sret */ MSVC struct-return convention (docs/LINUX.md "Struct returns")
#undef FontGetGlyphRect_26e040
void *FontGetGlyphRect_26e040(Rect *rg_ret, s32 arg1, s32 arg2) { *rg_ret = FontGetGlyphRect_26e040_sret(arg1, arg2); return rg_ret; }
#endif
