/* rgp:protos */
#define RGP_SELF_VariantGetInt_30ab50 1
#include "port/game_protos.h"
#line 1
/* VariantGetInt_30ab50 -- byte-identical clone of VariantGetInt_15f780 (52 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 6-member byte-identical group (52 B each):
   VariantGetInt_30ab50 / VariantGetInt_1c2bd0 / ScriptArgGetInt_1ecbe0 / ScriptArgGetInt_23fc00 / ScriptArgGetInt_301a60 /
   VariantGetInt_30ab50.  The s32 half of the VariantGetFloat_15f740 pair -- same `switch`,
   same reversed case order. */

struct Var5f780 {
    s32 tag;                    /* +0x00: 1 = s32, 2 = f32 */
    union {
        s32 i;
        f32 f;
    } v;                        /* +0x04 */
};

s32 VariantGetInt_30ab50(struct Var5f780 *p)
{
    switch (p->tag) {
    case 1:
        return p->v.i;
    case 2:
        return (s32)p->v.f;
    }
    return 0;
}
