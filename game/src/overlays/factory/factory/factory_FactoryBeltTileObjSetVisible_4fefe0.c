/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltTileObjSetVisible_4fefe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FEFE0 -- 72 bytes / 18 words, 3 branches, 0 calls.
 * Set or clear bit 0 of the target's 0x3C word depending on the request's
 * 0x20 byte, after two null guards.
 *
 * * `addiu $3, $0, -0x2` materialises the mask in a register: `~1` is the
 *   promoted `int` complement of a 32-bit field, not a 16-bit `andi`
 *   (the same shape as `p.f & ~3` in `factory_FactoryBeltResetAll_500f50`).
 * * `beql $3, $0, .L004FF018` with `lw $3, 0x3C($6)` in the LIKELY slot is
 *   the load of the else arm duplicated into the slot, i.e. one load per arm
 *   of a plain `if (b->f20 != 0) ... else ...`, not two loads.
 * * The two null guards both branch to the epilogue with a plain `beqz`+`nop`,
 *   so they are two separate early `return`s and not a `||` join.
 */

typedef struct Target {
    u8  pad00[0x3C];
    s32 f3C;
} Target;

typedef struct Req {
    u8  pad00[0x20];
    u8  f20;
    u8  pad21[0x3];
    s32 f24;
} Req;

typedef struct Owner {
    u8      pad00[0x20];
    Target *f20;
} Owner;

void factory_FactoryBeltTileObjSetVisible_4fefe0(Owner *o, Req *r)
{
    Target *t;

    t = o->f20;
    if (t == 0) {
        return;
    }
    if (r->f24 == 0) {
        return;
    }
    if (r->f20 != 0) {
        t->f3C = t->f3C & ~1;
    } else {
        t->f3C = t->f3C | 1;
    }
}
