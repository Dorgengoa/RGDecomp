/* rgp:protos */
#define RGP_SELF_VariantGetFloat_311e10 1
#include "port/game_protos.h"
#line 1
/* VariantGetFloat_311e10 -- byte-identical clone of VariantGetFloat_15f740 (56 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 6-member byte-identical group (56 B each):
   VariantGetFloat_311e10 / ScriptArgGetFloat_1ecba0 / ScriptArgGetFloat_23fbc0 / ScriptArgGetFloat_301a20 / VariantGetFloat_30ab10 /
   VariantGetFloat_311e10.  Read a tagged variant as f32.

   A `switch`, not an if-chain: retail's `beql` branches INTO each arm with
   the arm's own load in the likely slot, and the source case order is the
   compare chain REVERSED -- see [[insect-dispatch-branch-polarity]].  The
   chain tests 2 then 1, so the cases are written 1 then 2. */

struct Var5f740 {
    s32 tag;                    /* +0x00: 1 = s32, 2 = f32 */
    union {
        s32 i;
        f32 f;
    } v;                        /* +0x04 */
};

f32 VariantGetFloat_311e10(struct Var5f740 *p)
{
    switch (p->tag) {
    case 1:
        return (f32)p->v.i;
    case 2:
        return p->v.f;
    }
    return 0.0f;
}
