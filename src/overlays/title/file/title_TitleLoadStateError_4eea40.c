#include "types.h"

/* title.bin overlay, 0x004EEA40 -- two unrelated halves selected by the second
 * argument: a shutdown that maps a mode to a transition id, and a poll that
 * only fires once the pad reports a press.
 *
 * Every `bnel` delay slot in the mode chain carries the NEXT guard's constant
 * except the last, which carries the ELSE arm's argument -- so the chain has a
 * real `else` and it passes 0xB, the same value as the 5 case.
 *
 * Ã¢Ëœâ…Ã¢Ëœâ…Ã¢Ëœâ… THE SECOND HALF IS A TWO-CASE `switch`, AND AN if/else-if CHAIN OF THE
 * SAME SHAPE IS TWO WORDS LONGER.  The compare chain tests 1 then 0, which by
 * the reversed-case-order rule is source order `case 0: case 1:`.  What the
 * switch buys is the pair retail has and the chain cannot produce:
 * `beql $3,$0,<ret>` with the case-0 STORE IN THE DELAY SLOT.  Written as
 * `if (x == 1) goto armed; if (x == 0) x = 1; return 1;` mwcc branches on the
 * INVERSE (`bnezl`), so the store cannot fill the slot and it costs an extra
 * `li` and a `nop`; giving the ==0 arm its own `return 1` is worse still
 * (74 words against retail's 69).  Measured: chain 71, chain+return 74,
 * switch 69 = byte-identical.
 */

extern s16 D_00484204;
extern s16 D_00484208;
extern s32 D_004841FC;
extern s32 D_00484200;
extern void *D_004841E0;
extern const u8 D_004B2570;

extern void title_TitleLoadYesNoCursorBob_4edc00(void *o, void *unused, s32 flag);
extern void title_TitleLoadProgressWindowShow_4ede10(void *b, void *c);
extern void title_TitleLoadShowMsg_4eeb60(s32 a);
extern void title_TitleLoadFadeWidgets_4eda30(s32 a);
extern s32 func_1839F0(void *a, s32 b);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 title_TitleLoadStateError_4eea40(s32 a, s32 b)
{
    if (b != 0) {
        D_00484208 = 0;
        title_TitleLoadYesNoCursorBob_4edc00(0, (void *)1, 0);
        title_TitleLoadProgressWindowShow_4ede10((void *)2, 0);
        if (D_00484204 == 8) {
            title_TitleLoadShowMsg_4eeb60(0xA);
        } else if (D_00484204 == 5) {
            title_TitleLoadShowMsg_4eeb60(0xB);
        } else if (D_00484204 == 0xE) {
            title_TitleLoadShowMsg_4eeb60(0);
        } else if (D_00484204 == 0x10) {
            title_TitleLoadShowMsg_4eeb60(0x17);
        } else {
            title_TitleLoadShowMsg_4eeb60(0xB);
        }
        return 1;
    }
    switch (D_00484208) {
    case 0:
        D_00484208 = 1;
        break;
    case 1:
        if (func_1839F0((void *)&D_004B2570, D_004841FC | D_00484200) != 0) {
            title_TitleLoadShowMsg_4eeb60(-1);
            title_TitleLoadFadeWidgets_4eda30(2);
            func_28EDE0(D_004841E0, 8, 0);
        }
        break;
    }
    return 1;
}
