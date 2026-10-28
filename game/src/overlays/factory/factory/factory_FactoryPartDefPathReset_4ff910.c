/* rgp:protos */
#define RGP_SELF_factory_FactoryPartDefPathReset_4ff910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FF910 -- 68 bytes / 17 words, 0 branches, 0 calls.
 * Reset a cursor record: nine stores, two of which are the v == 0 instance of
 * the recorded `((h & ~3) | v) & 3` orientation rewrite.
 *
 * OVERTURNS the "13-spelling BOUNDED NEGATIVE" recorded for this symbol in
 * build/wf-parked/NEGATIVES.md (~line 565) and in the factory board.  The
 * claim was that mwcc folds `(x & ~3) & 3` to zero through every spelling; it
 * does, through every SINGLE-EXPRESSION spelling, but not through this one.
 *
 * * The fold is blocked by splitting the two masks across TWO statements with
 *   the FIRST mask inside the initialising assignment: `t = x & ~3;` then
 *   `x = t & 3;`.  Measured, 17 arms in one round trip:
 *     - `(x & ~3) & 3`, `((x & ~3) | 0) & 3`, no-cast, `0xFFFFFFFC`,
 *       `3 & (x & ~3)`, a named mask local (`m = ~3`, `m = 3` with `~m`),
 *       a named zero local for `v`, and the three-statement local form
 *       (`t = x; t = t & ~3; t = t & 3;`) ALL fold -- 10 words.
 *     - the COMPOUND form (`t = x; t &= ~3; x = t & 3;`) also folds, so this
 *       is NOT [[insect-compound-assign-blocks-fold]]; what matters is that
 *       the `& ~3` is the initialiser of the local, not a later step on it.
 *     - `((u32)(x & ~3)) % 4` is the only other arm that matches, and it is
 *       the same shape (an unsigned `% 4` mwcc lowers to `andi 3` after the
 *       AND is already committed to a temporary).
 * * `addiu $5, $0, -0x4` is materialised ONCE and shared by both fields: the
 *   `~3` is the promoted `int` complement, so it needs a register, and the
 *   two uses CSE.
 * * `sw $0, 0xC($4)` between the halfword stores is one 32-bit member, and the
 *   store order is SOURCE order.
 */

typedef struct Cursor {
    s16 f00;
    s16 f02;
    u16 f04;
    s16 f06;
    s16 f08;
    u16 f0A;
    s32 f0C;
    s16 f10;
    s16 f12;
} Cursor;

void factory_FactoryPartDefPathReset_4ff910(Cursor *c)
{
    u32 t;

    c->f00 = 0;
    c->f02 = 0;
    t = c->f04 & ~3;
    c->f04 = (u16)(t & 3);
    c->f06 = 0;
    c->f08 = 0;
    t = c->f0A & ~3;
    c->f0A = (u16)(t & 3);
    c->f0C = 0;
    c->f10 = 0;
    c->f12 = 0;
}
