/* rgp:protos */
#define RGP_SELF_factory_FactoryGridDirDy_4ff9b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FF9B0 -- copy the four-float table at 0x00480850
 * to the stack and return element `i & 3` of it as a raw word.
 * 60 bytes / 15 words.  TWIN of factory_FUN_004FF9F0 (table at 0x00480840).
 *
 * ** THE CONSTRUCT IS A STRUCT COPY, not four assignments.  Four element
 * assignments (`t[0] = D_00480850; ...`) put the FOURTH `lwc1` one slot too
 * early, at 0x004FF9D0, ahead of `swc1 $f2, 0x4($29)` -- 2 bad at the right
 * length.  Assigning a 4-float struct THROUGH A CAST emits the same eight
 * memory ops from a BATCHED loads-then-stores pre-order and lands retail's
 * schedule exactly.  [[main-pass34-substructs]] read in the source direction.
 *
 * ** The cast is load-bearing: `extern V4 D_00480850_s; t = D_00480850_s;`
 * (a DECLARED struct) is 16-byte aligned as far as mwcc is concerned and
 * collapses to an `lq`/`sq` pair -- 10 words, five short.  Casting the first
 * scalar hides the alignment and forces the member-wise float copy.
 *
 * ⚠ 42 measured cells say nothing else reaches it: 21 source spellings (named
 * result / named index before and after / a 4-member struct with four separate
 * member assignments / stores through a pointer / a union / `volatile f32
 * t[4]` / a named local for the fourth value / four named locals / a comma
 * expression / pointer-form read / an incomplete-array or `[2]`-array
 * declaration of the globals) are ONE object, 2 bad; and 21 codegen pragmas
 * (`schedule`, `no_branch_likely`, `conditional_move`, `late_conditional_move`,
 * `opt_repositioncode` both ways, `opt_movepostops` both ways, `cse_hard_reg_*`,
 * `reg_class_allocs`, `opt_propagation`, `opt_constnonchanging`, `opt_lifetimes`,
 * `opt_dead_assignments`, `opt_common_subs`, `opt_peephole`, `optimize_for_size`,
 * `opt_strength_reduction`, `usefloatacc`, `stdc_fp_contract`, `fastmath`,
 * `fast_fptosi`, levels 2/3) are the SAME object.  `schedule off` is +1 word.
 * ⚠ `extern f32 D_00480850[];` LEAVES SMALL DATA: +4 words (%hi/%lo), while
 * `extern f32 D_00480850[2];` keeps the gp form -- the sdata threshold is on
 * the DECLARED size.
 */

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

extern f32 D_00480850;

u32 factory_FactoryGridDirDy_4ff9b0(s32 i)
{
    V4 t __attribute__((aligned(16)));

    t = *(V4 *)&D_00480850;
    return ((u32 *)&t)[i & 3];
}
