#include "types.h"
/* insect 0x0051D1D0 -- 92 B / 23 words.  Member of the func_134A98 loader
 * family; the Ctx declaration and the `extern Ctx *D_00485170` (gp+0) spelling
 * are transcribed verbatim from the family seed
 * src/wf/insect/insect_InsectAbilityTableLoad_51d0b0.c, which already matches.
 *
 * `sw $0, 0x0($28)` is the gp global being cleared -- same publish/retract
 * idiom the seed uses around func_42FA20.
 * The clear loop runs i = 0..7 over 0x6C, so 0x8C is the member AFTER the
 * array; per insect-struct-overlap-declaration the [8]+named-field and the
 * [9]+last-element spellings are the same object, so the plain one is used.
 * `daddu $4, $0, $0` (i = 0) sits between the 0x58 and 0x64 stores -- loop
 * preheader scheduling, not a source order. */

typedef struct Ctx {
    u8  pad00[0x58];
    s32 m58;                    /* +0x58 */
    s32 m5C;                    /* +0x5C */
    s32 m60;                    /* +0x60 */
    s32 m64;                    /* +0x64 */
    u8  pad68[4];
    s32 m6C[8];                 /* +0x6C */
    s32 m8C;                    /* +0x8C */
} Ctx;

extern Ctx *D_00485170;

extern void func_14DFF0(Ctx *a);

void insect_InsectAbilityTableClear_51d1d0(Ctx *a)
{
    s32 i;

    func_14DFF0(a);
    a->m58 = 0;
    a->m64 = 0;
    a->m5C = 0;
    a->m60 = 0;
    D_00485170 = 0;
    for (i = 0; i < 8; i++) {
        a->m6C[i] = 0;
    }
    a->m8C = 0;
}
