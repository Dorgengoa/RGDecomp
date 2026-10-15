#include "types.h"

/* MAIN MainMenuPanelSetWidgetTex_297850 -- window 0x00296000-0x0029C000, the panel-handle
   D_004DB1B0 family (same handle as MainMenuPanelFadeOut_2968a0 / DebugItemIconGridShow_29a890).
   Store-dense, no gp: pass-34 sub-struct rules.

   Readings:
     * `andi $5,$4,0xFFFF` is the SETTLED main spelling `(id & 0xFFFF)` with
       both parameters s32 -- see the byte-identical src/wrappers/InsectInfoIconSetUvByIdMaybe_3929b0.c
       which calls the same UiFindWidget_290460 that way.
     * `beql $16,$0` jumps PAST the body to the epilogue, so the fall-through
       is the if BODY: the guard is the positive `if (p != 0)`.
     * `lw $3,0x20($16)` then FOUR `sh` through $3: the sub-struct pointer is
       read ONCE into a named local; the four stores are INTERLEAVED with
       nothing, so they are four separate source statements in listing order.
     * THE STORE ORDER IS 0x08, 0x0A, 0x0E, 0x0C -- 0x0E BEFORE 0x0C, both
       from the same $17.  That is source order showing through; writing
       0x0C before 0x0E is the obvious-but-wrong spelling.  */

typedef struct Sub97850 {
    u8 pad00[0x8];
    s16 m08;                 /* +0x08 */
    s16 m0A;                 /* +0x0A */
    s16 m0C;                 /* +0x0C */
    s16 m0E;                 /* +0x0E */
} Sub97850;

typedef struct Obj97850 {
    u8 pad00[0x4];
    char m04[0x1C];          /* +0x04, strcpy destination */
    Sub97850 *m20;           /* +0x20 */
} Obj97850;

extern Obj97850 *UiFindWidget_290460(void *, s32);
extern s32 strcpy(void *, void *);

extern u8 D_004DB1B0[];

void MainMenuPanelSetWidgetTex_297850(s32 id, void *name, s32 a, s32 b, s32 c)
{
    Obj97850 *p;
    Sub97850 *q;

    p = UiFindWidget_290460(D_004DB1B0, (id & 0xFFFF));
    if (p != 0) {
        strcpy(p->m04, name);
        q = p->m20;
        q->m08 = a;
        q->m0A = b;
        q->m0E = c;
        q->m0C = c;
    }
}
