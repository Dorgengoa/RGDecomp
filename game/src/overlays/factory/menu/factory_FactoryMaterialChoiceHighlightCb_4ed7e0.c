/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialChoiceHighlightCb_4ed7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004ED7E0 -- position the two page-flip arrows.
 *
 * ★ Guard polarity, the `return 0` case: retail branches INTO the body
 * (`bnez $16, .L004ED808`) and lets the failure fall through, so the source is
 * the INVERTED early return.  Written as `if (w != 0) { ...; return 1; }
 * return 0;` the exit lands on a branch to the epilogue instead.
 * ★ `sll 3 / subu / sll 2` is `* 0x1C`, mwcc's strength reduction -- not source.
 * ★ `k` is an `s32` local fed by an `lh` on an `s16` field: an `s16` LOCAL would
 * make the `xori` re-normalise with `dsll32`/`dsra32`.
 * ★★ DECLARATION ORDER is the lever for the callee-saved pair: with `w`
 * declared before `k` the two swap registers and the whole function reads 17
 * bad words with the right length.  `k` first is byte-identical, and so is any
 * order that puts `k` ahead of `w` (4 orders measured, 3 exact).
 */

typedef struct Page {
    u8  pad00[0x12];
    s16 f12;
} Page;

typedef struct View {
    u8    pad00[0x40];
    void *f40;
} View;

extern View *D_00484A58;                        /* _gp - 0x718 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialChoiceHighlightCb_4ed7e0(Page *o)
{
    s32   x;
    s32   y;
    s32   k;
    void *w;

    w = D_00484A58->f40;
    if (w == 0) {
        return 0;
    }
    UiGetWidgetPos_2910a0(w, 0x6D, &x, &y);
    k = o->f12;
    x = x + 6;
    y = y + (k * 0x1C + 5);
    UiSetWidgetPos_290f60(w, 0x67, x, y);
    UiSetSpriteW_28fbf0(w, 0x6D, 0, k);
    UiSetSpriteUvW_28f850(w, 0x6D, 0, k);
    k = k ^ 1;
    UiSetSpriteW_28fbf0(w, 0x6D, 0x3C, k);
    UiSetSpriteUvW_28f850(w, 0x6D, 4, k);
    return 1;
}
