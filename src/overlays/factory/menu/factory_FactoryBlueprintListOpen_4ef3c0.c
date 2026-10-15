#include "types.h"

/* factory.bin overlay, 0x004EF3C0 -- 360 B / 90 words, 6 branches, 11 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 * Same context (_gp - 0x728) as factory_FUN_004EF090 / 004EF2B0.
 *
 * SWITCH cell (lane fy01's family key): `b .L004EF51C / ld $31,0x0($29)` with
 * the `beql $2,$0` guard two rows above it, annulling the body's own
 * `lw $2,-0x728($28)`.  ONE trailing `return 1`.
 *
 * * `func_290460` returns a POINTER, not a flag: the `beql $2,$0` skip is
 *   followed by `lw $4,0x20($2)` off that same $2.  Name it, then test its
 *   `f20` in a nested `if` -- the annulled slot holds the MERGE's re-read of
 *   the gp global, which is the tell that the skip clears both tests.
 * * NO named local for the handle: every use re-reads `lw $2,-0x728($28)` and
 *   `lw $4,0x80($2)`.
 * * `-0x7EF8` is `D_0047D278` in mwcc's .lit4 literal pool.
 * * `s32 a; s32 b;` -> a at 0x1C($29), b at 0x18($29).
 */

typedef struct Slot {
    u8    pad00[0x20];
    void *f20;                                  /* +0x20 */
} Slot;

typedef struct Ctx {
    u8    pad00[0x6D];
    u8    f6D;                                  /* +0x6D */
    u8    pad6E[0x12];
    void *f80;                                  /* +0x80 */
    u8    pad84[0x4];
    void *f88;                                  /* +0x88 */
} Ctx;

extern Ctx *D_00484A48;                         /* _gp - 0x728  */
extern s32  D_00484B78;                         /* _gp - 0x5F8  */
extern f32  D_0047D278;                         /* _gp - 0x7EF8 */

extern void  factory_FactoryMenuCaptionSlideIn_4eb220(void);
extern void  factory_FactoryMenuCaptionSetRow_4eb270(s32 a);
extern void  factory_FactoryBlueprintListInit_4fbab0(Ctx *o);
extern void  func_28D580(void *p, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_28EDE0(void *ctx, s32 id, s32 a);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern Slot *func_290460(void *w, u16 id);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void  func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);
extern void  func_2910A0(void *w, s32 id, s32 *x, s32 *y);

s32 factory_FactoryBlueprintListOpen_4ef3c0(s32 unused, s32 start)
{
    s32   a;
    s32   b;
    Slot *s;

    if (start != 0) {
        func_290010(D_00484A48->f80, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(0);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        func_290010(D_00484A48->f80, 0x1F, 1, -1);
        s = func_290460(D_00484A48->f80, 0x20);
        if (s != 0) {
            if (s->f20 != 0) {
                func_28D580(s->f20, 0, 0, 0x199, 0x12C, 0);
            }
        }
        func_290F60(D_00484A48->f80, 0x1F, 0x200, 0x36);
        func_290F50(D_00484A48->f80, 0x1F, 0x37, 0x36, 0, D_0047D278);
        func_290690(D_00484A48->f80, 0x1F, 1.0f, 0.125f, 0.0f);
        factory_FactoryBlueprintListInit_4fbab0(D_00484A48);
        D_00484B78 = 0;
    }
    switch (D_00484B78) {
    case 0:
        func_2910A0(D_00484A48->f80, 0xC, &a, &b);
        if (a == 0) {
            if (b == 0) {
                D_00484B78 = -1;
                func_28EDE0(D_00484A48->f88, 0x88EA, 0);
                D_00484A48->f6D = 1;
            }
        }
        break;
    }
    return 1;
}
