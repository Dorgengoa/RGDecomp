#include "types.h"

/* factory.bin overlay, 0x004EF800 -- 248 B / 62 words, 4 branches, 7 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.  Twin of
 * factory_FUN_004EF900 over the other latch flag (-0x5C4 vs -0x5C8).
 *
 * SWITCH cell of the family key (lane fy01): `b .L004EF8E4` carries
 * `ld $31,0x20($29)` in its delay slot and the `beql $2,$0` guard is exactly
 * two rows above it, annulling the BODY's first instruction -- so
 * `switch (D_00484BAC) { case 0: ... break; } return 1;`, ONE trailing return.
 *
 * * Assign the 0x68 field FIRST: mwcc emits the two context loads in REVERSE
 *   source order, giving retail's `lw $16,0x70` then `lw $17,0x68` in the
 *   `beqz $5` delay slot.
 * * `func_290690(w, 0x53, 0.0f, -0.125f, 1.0f)` -- $f12/$f13/$f14 in argument
 *   order; the `lui 0xBE00` for -0.125f is scheduled first only because $f13's
 *   mtc1 is what the scheduler could hoist.
 * * `s32 x; s32 y;` in that order -> x at 0x3C($29), y at 0x38($29) (stack
 *   locals are allocated in REVERSE declaration order).
 * * The last `func_290010` takes a SEPARATE gp pointer, `D_004807E8`
 *   (`lw $4,-0x4988($28)`), not the panel handle.
 */

typedef struct Ctx {
    u8    pad00[0x68];
    void *f68;                                  /* +0x68 */
    u8    pad6C[0x4];
    void *f70;                                  /* +0x70 */
} Ctx;

extern Ctx  *D_00484A54;                        /* _gp - 0x71C  */
extern s32   D_00484BAC;                        /* _gp - 0x5C4  */
extern void *D_004807E8;                        /* _gp - 0x4988 */

extern void factory_FactoryMenuCaptionSlideOut_4eb1d0(void);
extern void func_28EDE0(void *ctx, s32 id, s32 a);
extern void func_290010(void *w, s32 id, s32 a, s32 b);
extern void func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void func_2910A0(void *w, s32 id, s32 *x, s32 *y);

s32 factory_FactoryRemoveStateClose_4ef800(s32 unused, s32 start)
{
    void *w;
    void *ctx;
    s32   x;
    s32   y;

    w = D_00484A54->f68;
    ctx = D_00484A54->f70;
    if (start != 0) {
        factory_FactoryMenuCaptionSlideOut_4eb1d0();
        func_290690(w, 0x53, 0.0f, -0.125f, 1.0f);
        D_00484BAC = 0;
    }
    switch (D_00484BAC) {
    case 0:
        func_2910A0(w, 0xC, &x, &y);
        if (x == -0xAA) {
            if (y == 0) {
                D_00484BAC = -1;
                func_28EDE0(ctx, 0x88CC, 0);
                func_290010(w, 0xC, 0, -1);
                func_290010(w, 0x53, 0, -1);
                func_290010(D_004807E8, 0x97, 0, -1);
            }
        }
        break;
    }
    return 1;
}
