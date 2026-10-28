/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceConsumeMaterials_4f4f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F4F80 -- 124 bytes / 31 words.  Walk the module's
 * four-entry (id, value) table and re-post every non-empty entry.
 *
 * ★ THE PARK IS OVERTURNED, and the key is a SECOND `volatile`.
 *
 * Retail reads `p->f00` TWICE -- once into $3 for the loop-head guard and
 * again into $5 as the argument -- and mwcc CSEs those two reads in every
 * non-volatile spelling (17 measured, all one object, 0x78 vs 0x7C: ONE WORD
 * SHORT).  `volatile s32 f00` restores the second load, but it also makes that
 * load a scheduling ANCHOR, so mwcc emits it FIRST and the call-setup block
 * comes out as `lw $5,0x0($18)` / `lw $4,0x18($16)` where retail has them the
 * other way round -- right length, TWO TRANSPOSED WORDS.
 *
 * The fix is not to fight the anchor but to JOIN it: mark `Ctx::f18` volatile
 * as well.  Two volatile accesses are ordered with respect to EACH OTHER, and
 * source order is `ctx->f18` then `p->f00`, which is exactly retail's order.
 * The non-volatile `p->f04` is free and already fell third on its own.
 *
 * * Measured: the volatile-f18 object is reached by TEN different spellings
 *   (s32 / `volatile VP` / `void *volatile` for the field; `&&` or nested
 *   `if`; a named `w = ctx->f18` local; f04 volatile as well; and with
 *   `#pragma optimization_level 3`) -- all sha1 3b1d94a0.  The field's TYPE,
 *   the join form and the pragma are all INERT; the second `volatile` is the
 *   entire lever.
 * * `#pragma optimization_level 3` on the plain source is a measured NULL
 *   here: byte-identical object to no pragma at all.
 * * `beql $3,$0` at the loop head skips straight to the test with the
 *   `addiu $17,$17,1` in the likely slot, while the `ctx` guard is a plain
 *   `beqz` to a duplicated increment; both are mwcc's own choice.
 * * `addiu $18,$18,8` sits in the loop-back branch's delay slot, so the
 *   pointer bump is a separate `p++` statement at the end of the body, not a
 *   third clause in the `for` header.
 */

typedef struct Ctx  { u8 pad00[0x18]; void *volatile f18; } Ctx;
typedef struct Pair { volatile s32 f00; s32 f04; } Pair;

typedef struct Mod {
    u8    pad00[0x80];
    Pair *f80;
} Mod;

/*rgp*/
/*rgp*/

void factory_FactoryProduceConsumeMaterials_4f4f80(Mod *o)
{
    Ctx  *ctx;
    Pair *p;
    s32   i;

    ctx = ((Ctx *)GetGameData_1fede0());
    p = o->f80;
    for (i = 0; i < 4; i++) {
        if (p->f00 != 0 && ctx != 0) {
            InvConsumeById_3c46b0(ctx->f18, p->f00, p->f04, 0, 1);
        }
        p++;
    }
}
