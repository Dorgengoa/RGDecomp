/* rgp:protos */
#define RGP_SELF_factory_FactoryMarkerFindFree_4f6280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F6280 -- 68 bytes / 17 words, 3 branches, 0 calls.
 * Return the index of the first free slot in the six-entry 0x14-stride table at
 * `0x78` (free == the `0x0E` byte is zero), or -1.
 *
 * Sub-family E of lane fy04 -- the only member that returns an INDEX rather
 * than a pointer or a sum.
 *
 * * `dsll32 $2,$3,16 / dsra32 $2,$2,16` is on the loop COUNTER at the return,
 * not inside the body: the return type is `s16` and `i` is a plain s32 local
 * ([[normal-s16-cast-sign-extension]] -- an `s16 i` is the measured null and
 * would truncate at every `addiu`).
 * * `lbu` makes the tested field `u8`; `bnel $2, $0` PAST the return is
 * `if (p->f0E == 0) return i;`.
 * * BOTH `return -1` blocks exist in retail (one for the NULL guard, one after
 * the loop) and the loop-exit copy rides in the loop-test likely slot; they do
 * not tail-merge because the guard's copy branches to the shared `jr`.
 */

typedef struct Ent {
    u8   pad00[0xE];
    u8   f0E;
    u8   pad0F[0x5];
} Ent;

typedef struct Ctx {
    u8    pad00[0x78];
    Ent  *f78;
} Ctx;

s16 factory_FactoryMarkerFindFree_4f6280(Ctx *c)
{
    Ent *p;
    s32  i;

    p = c->f78;
    if (p == 0) {
        return -1;
    }
    for (i = 0; i < 6; i++, p++) {
        if (p->f0E == 0) {
            return i;
        }
    }
    return -1;
}
