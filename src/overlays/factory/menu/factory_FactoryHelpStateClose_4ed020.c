#include "types.h"

/* factory.bin overlay, 0x004ED020 -- 288 B / 72 words, 4 branches, 7 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 *
 * SWITCH cell (lane fy01's family key): the `beql $2,$0` guard is exactly two
 * rows above `b .L004ED12C / ld $31,0x20($29)` and annuls the BODY's own first
 * instruction, so the source is one `switch` arm plus ONE trailing `return 1`.
 *
 * * Assign the 0x88 field FIRST -- mwcc emits the two context loads in REVERSE
 *   source order, giving `lw $16,0x90` then `lw $17,0x88` in the `beqz $5` slot.
 * * `s32 x; s32 y;` -> x at 0x3C($29), y at 0x38($29) (stack locals are
 *   allocated in REVERSE declaration order).
 * * `func_28F670`'s four 0x40 arguments share one register: retail materialises
 *   0x40 into $6 and copies it into $7/$8/$9.  That is mwcc CSE-ing the
 *   literal, not a source-level temporary.
 */

typedef struct Ctx {
    u8    pad00[0x88];
    void *f88;                                  /* +0x88 */
    u8    pad8C[0x4];
    void *f90;                                  /* +0x90 */
} Ctx;

extern Ctx *D_00484A5C;                         /* _gp - 0x714  */
extern s32  D_00484AE4;                         /* _gp - 0x68C  */
extern f32  D_0047D4E4;                         /* _gp - 0x7C8C */

extern void factory_FactoryMenuCaptionSlideOut_4eb1d0(void);
extern void func_28EDE0(void *ctx, s32 id, s32 a);
extern void func_28F670(void *w, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_290010(void *w, s32 id, s32 a, s32 b);
extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void func_2910A0(void *w, s32 id, s32 *x, s32 *y);

s32 factory_FactoryHelpStateClose_4ed020(s32 unused, s32 start)
{
    void *w;
    void *ctx;
    s32   x;
    s32   y;

    w = D_00484A5C->f88;
    ctx = D_00484A5C->f90;
    if (start != 0) {
        factory_FactoryMenuCaptionSlideOut_4eb1d0();
        func_290F50(w, 0x7C, 0x200, 0x36, 0, D_0047D4E4);
        func_290690(w, 0x7C, 0.0f, -0.125f, -1.0f);
        D_00484AE4 = 0;
    }
    switch (D_00484AE4) {
    case 0:
        func_2910A0(w, 0xC, &x, &y);
        if (x == -0xAA) {
            if (y == 0) {
                D_00484AE4 = -1;
                func_28EDE0(ctx, 0x88CC, 0);
                func_28F670(w, 0x7F, 0x40, 0x40, 0x40, 0x40, 0);
                func_290010(w, 0xC, 0, -1);
                func_290010(w, 0x7C, 0, -1);
            }
        }
        break;
    }
    return 1;
}
