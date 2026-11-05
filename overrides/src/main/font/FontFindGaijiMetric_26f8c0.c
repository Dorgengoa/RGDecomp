/* rg-override: replaces game/src/main/font/FontFindGaijiMetric_26f8c0.c sha256 8330e935f28493d42b0e9c49d2f334799104f7fbaa5de1d5a2ea7a808cd31da1
 * why: keyboard prompts with full key names (docs/PROMPTS.md "Width changes (--wide)", lane
 * p6a11y 2026-11-01): the one gaiji metric lookup every text path uses (drawing, measuring,
 * wrapping) reads the port's copy of the 12-byte record table while the keyboard style with
 * wide glyphs is in the gaiji2 texture (rg_game_gaiji_metrics, src/game/rg_game_main.c), so
 * text measures, wraps and draws with the same advance; NULL (every other style, the Original
 * preset, every scripted run) = the game's own D_0044E680, unchanged.  The FD3E -> FD3F rule
 * is the game's. */
/* rgp:protos */
#define RGP_SELF_FontFindGaijiMetric_26f8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u16 D_0044E680[];

/* (port, src/game/rg_game_main.c) the active metric table, or NULL for the game's */
u16 *rg_game_gaiji_metrics(void);

u16 *FontFindGaijiMetric_26f8c0(s32 arg0, s32 arg1)
{
    u16 key;
    u16 *p;
    u16 temp;

    key = (u16)arg1;
    if (key == 0xFD3E && ((signed char)TextStyleGetFontType_26ede0((void *)arg0)) == 2) {
        key = 0xFD3F;
    }
    p = rg_game_gaiji_metrics();
    if (p == NULL) {
        p = D_0044E680;
    }
    while ((temp = *p) != 0) {
        if (temp == key) {
            return p;
        }
        p += 6;
    }
    return NULL;
}
