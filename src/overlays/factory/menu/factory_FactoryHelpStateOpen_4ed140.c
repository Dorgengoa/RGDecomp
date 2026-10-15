#include "types.h"

/* factory.bin overlay, 0x004ED140 -- 424 B / 106 words, 5 branches, 14 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.  Same context
 * (_gp - 0x714) as factory_FUN_004ED020, neighbouring flag (-0x690).
 *
 * SWITCH cell (lane fy01 family key): `b .L004ED2D4 / ld $31,0x20($29)` with
 * the `beql $2,$0` guard exactly two rows above it, annulling the body own
 * `daddu $4,$17,$0`.  ONE trailing `return 1`.
 *
 * * Assign the 0x88 field FIRST -- loads are emitted in REVERSE source order.
 * * `func_290460` returns a POINTER; the `beql $2,$0` skip is followed by
 *   `lw $4,0x20($2)` off that same $2, so it is `if (s) { if (s->f20) ... }`.
 * * The repeated literals are mwcc CSE, not source temporaries: func_28F670
 *   five zeros are five `daddu $0` and func_290F50 `daddu $7,$6,$0` copies
 *   the 0x36 already in $6.
 * * `-0x7EF8` is `D_0047D278` in the mwcc .lit4 literal pool.
 * * `s32 x; s32 y;` -> x at 0x3C($29), y at 0x38($29).
 */

typedef struct Slot {
    u8    pad00[0x20];
    void *f20;                                  /* +0x20 */
} Slot;

typedef struct Ctx {
    u8    pad00[0x88];
    void *f88;                                  /* +0x88 */
    u8    pad8C[0x4];
    void *f90;                                  /* +0x90 */
} Ctx;

extern Ctx *D_00484A5C;                         /* _gp - 0x714  */
extern s32  D_00484AE0;                         /* _gp - 0x690  */
extern f32  D_0047D278;                         /* _gp - 0x7EF8 */

extern void  factory_FactoryMenuCaptionSlideIn_4eb220(void);
extern void  factory_FactoryMenuCaptionSetRow_4eb270(s32 a);
extern void  factory_FactoryHelpOpen_4f1f80(Ctx *o);
extern void  func_28D580(void *p, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_28EDE0(void *ctx, s32 id, s32 a);
extern void  func_28F670(void *w, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_28FB10(void *w, s32 id, s32 a, s32 b, s32 c);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern Slot *func_290460(void *w, u16 id);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void  func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);
extern void  func_2910A0(void *w, s32 id, s32 *x, s32 *y);

s32 factory_FactoryHelpStateOpen_4ed140(s32 unused, s32 start)
{
    Slot *s;
    void *w;
    void *ctx;
    s32   x;
    s32   y;

    w = D_00484A5C->f88;
    ctx = D_00484A5C->f90;
    if (start != 0) {
        func_290010(w, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(5);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        func_290010(w, 0x7C, 1, -1);
        s = func_290460(w, 0x7F);
        if (s != 0) {
            if (s->f20 != 0) {
                func_28D580(s->f20, 0, 0, 0x193, 0x154, 0);
            }
        }
        func_28F670(w, 0x7F, 0, 0, 0, 0, 0);
        func_28FB10(w, 0x7D, 0x175, 0x133, 0);
        func_28FB10(w, 0x7E, 0x175, -0x270F, 0);
        func_290F60(w, 0x7C, 0x200, 0x36);
        func_290F50(w, 0x7C, 0x36, 0x36, 0, D_0047D278);
        func_290690(w, 0x7C, 1.0f, 0.125f, 0.0f);
        factory_FactoryHelpOpen_4f1f80(D_00484A5C);
        D_00484AE0 = 0;
    }
    switch (D_00484AE0) {
    case 0:
        func_2910A0(w, 0xC, &x, &y);
        if (x == 0) {
            if (y == 0) {
                D_00484AE0 = -1;
                func_28EDE0(ctx, 0x89DA, 0);
            }
        }
        break;
    }
    return 1;
}
