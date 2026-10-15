#include "types.h"

/* factory.bin overlay, 0x004EE7D0 -- 320 B / 80 words, 5 branches, 7 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 * Sibling of factory_FUN_004EE910 over the same context (_gp - 0x720) and a
 * neighbouring done-flag (-0x644 vs -0x648).
 *
 * SWITCH cell (lane fy01's family key): `b .L004EE8FC / ld $31,0x20($29)` with
 * the `beql $2,$0` guard exactly two rows above it, annulling the body's own
 * `daddu $4,$17,$0`.  ONE trailing `return 1`.
 *
 * * Assign the 0x60 field FIRST -- loads are emitted in REVERSE source order.
 * * The `f70 == 1` test appears TWICE and each site re-reads the gp global;
 *   mwcc does not CSE a gp load across a call, and `lbu` says the field is u8.
 * * In the start arm that test is a `bnel` PAST the arm whose annulled slot
 *   holds the MERGE's own `lui 0xBE000000`; at the tail it is a plain `bne`
 *   because nothing follows it to steal.
 * * `s32 x; s32 y;` -> x at 0x3C($29), y at 0x38($29).
 */

typedef struct Ctx {
    u8    pad00[0x60];
    void *f60;                                  /* +0x60 */
    u8    pad64[0x4];
    void *f68;                                  /* +0x68 */
    u8    pad6C[0x4];
    u8    f70;                                  /* +0x70 */
} Ctx;

extern Ctx *D_00484A50;                         /* _gp - 0x720 */
extern s32  D_00484B2C;                         /* _gp - 0x644 */

extern void factory_FactoryMenuCaptionSlideOut_4eb1d0(void);
extern void func_28EDE0(void *ctx, s32 id, s32 a);
extern void func_290010(void *w, s32 id, s32 a, s32 b);
extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void func_2907A0(void *w, s32 id, f32 v);
extern void func_2910A0(void *w, s32 id, s32 *x, s32 *y);

s32 factory_FactoryMoveStateClose_4ee7d0(s32 unused, s32 start)
{
    void *w;
    void *ctx;
    s32   x;
    s32   y;

    w = D_00484A50->f60;
    ctx = D_00484A50->f68;
    if (start != 0) {
        factory_FactoryMenuCaptionSlideOut_4eb1d0();
        if (D_00484A50->f70 == 1) {
            func_290690(w, 0xC, 0.0f, 1.0f, -1.0f);
        }
        func_290690(w, 0x4D, 0.0f, -0.125f, 1.0f);
        D_00484B2C = 0;
    }
    switch (D_00484B2C) {
    case 0:
        func_2910A0(w, 0xC, &x, &y);
        if (x == -0xAA) {
            if (y == 0) {
                D_00484B2C = -1;
                func_28EDE0(ctx, 0x88CC, 0);
                func_290010(w, 0xC, 0, -1);
                func_290010(w, 0x4D, 0, -1);
                if (D_00484A50->f70 == 1) {
                    func_2907A0(w, 0xC, 1.0f);
                }
            }
        }
        break;
    }
    return 1;
}
