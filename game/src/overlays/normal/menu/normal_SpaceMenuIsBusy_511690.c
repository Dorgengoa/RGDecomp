/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuIsBusy_511690 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00511690 -- a four-way predicate on one record byte.
 * ★ The FIRST compare lands in a GPR (`slti $3, $4, 0x2`) and the second in
 * `$at` (`slti $1, $4, 0x8`), and only the first is a source lever.  Per
 * [[at-compare-class]] the destination follows the branch's RELATIONAL
 * OPERATOR TOKEN: `if (v >= 2)` gives the GPR and `if (v > 1)` gives `$at`,
 * two words apart on the identical instruction.  ⚠ The inner compare is NOT
 * token-driven -- `v > 7` and `v >= 8` both give `$at` here (measured), so
 * that one is real pressure and the token rule had nothing to do with it.
 * ★ `v = (s32)p->f14;` into an `s16` local is what produces retail's
 * `dsll32 16 / dsra32 16` re-normalisation of the `lbu`; WITHOUT the cast the
 * value provably fits and mwcc drops both words.
 * ★ The `v <= 1` case is the FALL-THROUGH into the shared `r = 1` block, not
 * an arm of its own -- written as `if (v < 2) { r = 1; goto done; }` mwcc
 * emits a separate `b`/`li` pair and the exit stops being a likely branch.
 * ★ And `v` is an `s16` LOCAL holding a `u8` FIELD: retail re-normalises the
 * `lbu` with `dsll32 16 / dsra32 16`, which is the mirror of the recorded
 * "an `s8` local costs two words" -- here the two words are wanted.
 * The `p == 0` arm is PHYSICALLY LAST, immediately before the epilogue, so it
 * is a `goto` label and not an `else`.
 * One of the 55 unnamed functions. */
typedef struct Rec {
    u8 pad00[0x14];
    u8 f14;
} Rec;

extern Rec *D_004846B8;

s32 normal_SpaceMenuIsBusy_511690(void)
{
    Rec *p;
    s16 v;
    s32 r;

    r = 0;
    p = D_004846B8;
    if (p == 0) {
        goto pnull;
    }
    v = (s32)p->f14;
    if (v >= 2) {
        if (v > 7) {
            goto one;
        }
        if (v != 3) {
            goto done;
        }
    }
one:
    r = 1;
    goto done;
pnull:
    r = 1;
done:
    return r;
}
