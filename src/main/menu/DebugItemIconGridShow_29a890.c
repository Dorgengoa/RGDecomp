#include "types.h"

/* MAIN DebugItemIconGridShow_29a890 -- panel layout for D_004DB1B0 (the same panel handle
   MainMenuPanelFadeOut_2968a0 drives).  Struct-initialiser shaped: 11-argument
   UiSetSpritePosSizeUv_28f710 calls whose 3rd/4th arguments come from four NAMED LOCALS
   derived from the caller's s16 fields.

   The four locals are the reading: their `lh`+`sll` are all HOISTED above the
   FIRST call, which uses none of them, and they live in $16..$19 across three
   calls -- an inline expression would be computed at its own call site.
   UiSetSpritePos_28fd10 then reuses them as `x2 - 8` / `x3 + 8`.

   `beqz $5` jumps PAST the body, so the fall-through is the if BODY:
   the guard is the positive `if (b != 0)`, and `a->m10 = b` sits in its
   delay slot because it precedes the test unconditionally.
   `a->m10` is RE-READ twice after the body (two `lw 0x10($20)`) -- two
   separate source reads.

   TWO MEASURED LEVERS:
     * `D_004DB1C0` must be declared as an ARRAY LONGER THAN 8 BYTES.
       Declared as a bare `extern s16` mwcc puts it in SMALL DATA and emits
       `sh $4,%gp_rel(..)($28)` -- ONE WORD SHORT of retail's `lui %hi` +
       `sh %lo`.  `extern s16 D_004DB1C0[8];` + `D_004DB1C0[0]` is the fix
       ([[im-gp-array-sdata-threshold]], and it transfers to MAIN).
     * the four derived locals are DECLARED AND ASSIGNED in the order
       m04, m06, m00, m02 -- that is retail's `lh` order and it is what puts
       them in $19,$18,$17,$16.  Declaring them m00..m06 gives the reversed
       register assignment and 5 wrong words.  BYTE-IDENTICAL.  */

typedef struct Ctx2A890 {
    s16 m00;                 /* +0x00 */
    s16 m02;                 /* +0x02 */
    s16 m04;                 /* +0x04 */
    s16 m06;                 /* +0x06 */
    u8 pad08[0x4];
    s16 m0C;                 /* +0x0C */
    u8 pad0E[0x2];
    s32 m10;                 /* +0x10 */
} Ctx2A890;

extern u8 D_004DB1B0[];
extern s16 D_004DB1C0[8];

extern void UiSetSpritePosSizeUv_28f710(void *, s32, s32, s32, s32, s32, s32, s32,
                         s32, s32, s32);
extern void UiSetSpritePos_28fd10(void *, s32, s32, s32, s32);
extern void DebugItemIconGridSetScrollThumbs_29a7e0(Ctx2A890 *);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);

void DebugItemIconGridShow_29a890(Ctx2A890 *a, s32 b)
{
    s32 x2;
    s32 x3;
    s32 x0;
    s32 x1;

    a->m10 = b;
    if (b != 0) {
        x2 = (a->m04 << 5) + 0x10;
        x3 = (a->m06 << 5) + 0x10;
        x0 = a->m00 << 5;
        x1 = a->m02 << 5;
        UiSetSpritePosSizeUv_28f710(D_004DB1B0, 0x1CC, 0xE, 0xE, 0x15C, 0x17C, 0x21, 0x26,
                     0x16, 8, 0);
        UiSetSpritePosSizeUv_28f710(D_004DB1B0, 0x1CC, x2, x3, 0x20, 0x20, 0xD, 0x63,
                     0xC, 6, 1);
        UiSetSpritePosSizeUv_28f710(D_004DB1B0, 0x1CD, 0x10, 0x10, 0x180, 0x140, x0, x1,
                     0x140, 0x100, 0);
        UiSetSpritePos_28fd10(D_004DB1B0, 0x1CE, x2 - 8, x3 + 8, 0);
        DebugItemIconGridSetScrollThumbs_29a7e0(a);
        a->m0C = 0;
    }
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x1CC, a->m10, 1);
    D_004DB1C0[0] = a->m10 ^ 1;
}
