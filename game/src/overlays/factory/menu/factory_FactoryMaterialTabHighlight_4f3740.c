/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialTabHighlight_4f3740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F3740 -- retint the five blueprint tab strips,
 * three cells each, with the selected one highlighted.  432 bytes, 108
 * instructions, 2 conditional branches, 7 calls (br/ins 0.019).
 *
 * SOLVED (fy22H).  The 4-word residue was the CSE the previous session
 * described: retail computes `i * 3` TWICE per arm -- once into a dying `$2`
 * for the first call, once into the callee-saved `$18` for the second and
 * third.  [[insect-cse-two-spellings]] closes it, but ONLY with a spelling
 * that both breaks the CSE AND keeps the multiply's operand order:
 *   - `(i << 1) + i` / `i + (i << 1)` break the CSE (length becomes exact)
 *     but emit `addu $18, $16, $2` -- leaf first -- and are the SAME object as
 *     each other: the SOURCE operand order of a `+` is IGNORED.  2 bad words.
 *   - `(s32)((u32)i * 3)` is an UNSIGNED multiply: a distinct tree from the
 *     signed `i * 3` (so no CSE) that still strength-reduces to
 *     `sll` + `addu $18, $2, $16` -- shift first, like retail.  MATCH.
 * ⇒ mwcc emits `addu d, <strength-reduced shift>, <base>` for a MULTIPLY and
 *   `addu d, <leaf>, <computed>` for a source-level `+`.
 *
 * ★ `func_28F710` takes ELEVEN arguments: eight in $4..$11 and three in the
 * 8-byte outgoing slots at 0x0/0x8/0x10($29).  The list has to be read off the
 * FRAME, not guessed from the callee ([[overlay-factory]]).
 *
 * ★ `slti $2, $16, 0x5` lands in a GPR, so the latch token is `i < 5`.
 */

typedef struct Tab {
    u8    pad00[0x4];
    s16   f04;
    u8    pad06[0x3A];
    void *f40;
} Tab;

/*rgp*/

/*rgp*/

void factory_FactoryMaterialTabHighlight_4f3740(Tab *o)
{
    s32 i;
    s32 k;

    for (i = 0; i < 5; i++) {
        if (o->f04 == i) {
            UiSetSpritePosSizeUv_28f710(o->f40, 0x5E, -0x270F, -0x1B, -0x270F, 0x2A, -0x270F, 0,
                        -0x270F, 0x2A, i * 3);
            k = (s32)((u32)i * 3);
            UiSetSpritePosSizeUv_28f710(o->f40, 0x5E, -0x270F, -0x1B, -0x270F, 0x2A, -0x270F, 0,
                        -0x270F, 0x2A, k + 1);
            UiSetSpritePosSizeUv_28f710(o->f40, 0x5E, -0x270F, -0x1B, -0x270F, 0x2A, -0x270F, 0,
                        -0x270F, 0x2A, k + 2);
        } else {
            UiSetSpritePosSizeUv_28f710(o->f40, 0x5E, -0x270F, -0x19, -0x270F, 0x1C, -0x270F, 0x2A,
                        -0x270F, 0x1C, i * 3);
            k = (s32)((u32)i * 3);
            UiSetSpritePosSizeUv_28f710(o->f40, 0x5E, -0x270F, -0x19, -0x270F, 0x1C, -0x270F, 0x2A,
                        -0x270F, 0x1C, k + 1);
            UiSetSpritePosSizeUv_28f710(o->f40, 0x5E, -0x270F, -0x19, -0x270F, 0x1C, -0x270F, 0x2A,
                        -0x270F, 0x1C, k + 2);
        }
    }
    factory_FactoryMaterialGridRefresh_4f3730(o, 0x61);
}
