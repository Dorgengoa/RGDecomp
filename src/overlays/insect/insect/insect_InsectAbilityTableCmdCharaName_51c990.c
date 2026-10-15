#include "types.h"
/* insect 0x0051c990 -- 80 B / 20 words.  RANK-5 twin cluster
 * (0051c940 / 0051c990 / 0051cd60): three functions whose listings differ in
 * exactly ONE word, the $4 setup before func_134A98.
 *
 * D_00485170 is _gp+0x0 and is a Ctx * -- settled by
 * src/overlays/insect/insect_InsectAbilityTableCmdNextRecord_51c900.c, whose `bnel` null-context guard and
 * s32 "context was there" predicate are transcribed here verbatim.  The
 * member at +0x64 is an s32 there; here it is dereferenced as a pointer, so
 * it is spelled u8 * in this TU.
 *
 * func_15F720 is called with NO argument setup (the jal's delay slot is a
 * nop and $4 is written only afterwards), so it is (void) here even though
 * insect_InsectLiveTalkTableCmdName_523970.c declares it with one parameter.
 *
 * MEASURED: the second guard MUST be spelled as the positive fall-through,
 * `if (t != 0) { call; return 1; } return 0;`.  The natural early-exit
 * spelling `if (t == 0) { return 0; } call; return 1;` compiles to 0x58 --
 * TWO WORDS LONG -- on this exact body (one round trip, tag wf31).
 */

typedef struct Ctx {
    u8  pad00[0x58];
    s32 m58;                    /* +0x58 */
    u8  pad5C[0x64 - 0x5C];
    u8 *m64;                    /* +0x64 */
    s32 m68;                    /* +0x68 */
} Ctx;

extern Ctx *D_00485170;

extern s32  func_15F720(void);
extern void func_134A98(void *a, s32 b);

s32 insect_InsectAbilityTableCmdCharaName_51c990(void)
{
    Ctx *g;
    u8 *t;

    g = D_00485170;
    if (g == 0) {
        return 0;
    }
    t = g->m64;
    if (t != 0) {
        func_134A98(t + 0x50, func_15F720());
        return 1;
    }
    return 0;
}
