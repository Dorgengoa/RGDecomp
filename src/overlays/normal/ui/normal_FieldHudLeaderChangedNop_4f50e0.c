#include "types.h"
#pragma optimization_level 1
/* normal 0x004F50E0 -- three words: `lh $3, 0x378($4) / jr $31 / nop`.
 * The loaded value lands in $3, NOT the return register $2, so the result is
 * discarded -- a read kept alive only because the member is volatile.  Retail
 * leaves the `jr` delay slot EMPTY, so the load was not scheduled into it.
 *
 * ★★★★★★ CLOSED, s27, BY `#pragma optimization_level 1` -- a knob OUTSIDE the
 * `opt_*` / `scheduling` namespace.  At the -O4 default mwcc sinks the `lh`
 * into the `jr` delay slot and the unit is TWO words; at level 1 it emits
 * `lh / jr / nop` and the unit is BYTE-IDENTICAL.
 * ⚠⚠ The `opt_*` namespace is a CLEAN 14-ARM NULL here -- `scheduling off`,
 * `no_branch_likely on`, `opt_propagation off`, `peephole off`,
 * `optimize_for_size on`, `opt_dead_code off`, `opt_unroll_loops off`,
 * `opt_common_subs off`, `opt_lifetimes off`, `opt_strength_reduction off`,
 * `opt_strength_reduction_strict on`, `opt_vectorize_loops off`,
 * `always_inline off`, `opt_dead_assignments off` -- all 2 words.
 * ARMED: `optimization_level 0` gives 7 words and `opt_level 0` gives 2, so the
 * pragma line demonstrably reaches mwcc and the null is a real null.
 * `build/wf-normal/s27/knob50e0.py`. */
typedef struct N {
    u8  pad000[0x378];
    s16 f378;
} N;

void normal_FieldHudLeaderChangedNop_4f50e0(N *p)
{
    *(volatile s16 *)&p->f378;
}
