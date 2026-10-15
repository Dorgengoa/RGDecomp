#pragma optimization_level 3

#include "types.h"

/* factory.bin overlay, 0x004FCDD0 -- 268 bytes / 67 words, 8 branches,
 * 4 calls.  Push the two spinner readings into the two counters, but only
 * when they actually moved.
 *
 * ** #pragma optimization_level 3 IS THE KEY, and it is the `||` lever.  At
 *    -O4 mwcc RANGE-FOLDS `(st==1)||(st==2)||(st==3)` -- consecutive constants
 *    on one CSE'd load -- into `addiu $3,$3,-1 / sltiu $1,$3,3 / beqz`, and
 *    the unit comes out EIGHT WORDS SHORT.  At -O3 the fold is gone and the
 *    short-circuit chain survives: `beql 1` and `beq 2` INTO the body, `bnel
 *    != 3` PAST it, last test inverted, fall-through.  Measured alternatives
 *    that do NOT reach it, all at the right shape but 2-4 words long: a
 *    `switch` with ascending cases (+4), with DESCENDING cases (+4), with the
 *    body moved outside via `case 1: break; default: return;` (+4).  A switch
 *    always branches INTO its last arm; only `||` inverts the last test.
 * * The `Dlg` container is the byte-identical `factory_FactoryRemoveDialogConfirm_4fcb60` /
 *   `factory_FactoryRemoveWaitRequest_4fcc50` verbatim, plus `f5C` (the `lw`/`sw` cached
 *   reading) and `f68` (the second widget handle).
 * * `addiu $16, $2, 0x4` on `func_28EA40`'s result is `factory_FactoryRemoveDialogConfirm_4fcb60`'s
 *   sub-struct address, taken once and reused on every arm.
 * * The tell that the three tests share ONE body is the DUPLICATED first
 *   instruction of that body in the `beql` delay slot: `lw $4,0x6C($17)` at
 *   0x004FCDF0 and again at 0x004FCE0C, `lw $4,0x5C($17)` at 0x004FCE68 and
 *   again at 0x004FCE78.
 * * `beq $3, $6, <exit>` (0x004FCE30) jumps PAST the second guard, so the
 *   "reading unchanged" case is an explicit `return`, not an `if` around the
 *   body.  Nesting it costs exactly two words: mwcc then emits `beql` into
 *   the second guard with the `lbu $4,0x64` duplicated in the likely slot,
 *   and it does NOT thread the branch even though `o->f64` is provably 1 on
 *   that path.
 * * `o->f64` is RE-READ with a fresh `lbu` after `func_28EA40` and again after
 *   the first block: `$4` is caller-saved, so the state is three separate
 *   `o->f64` reads in source, not one named local.
 * * `mult $2, $6, $2` takes the compare's already-loaded `b->f12` as the LEFT
 *   operand, so the product is written `b->f12 * b->f06`, and `addu $6,$2,$3`
 *   puts the `+ 2` term first: `r->f00 + 2 + b->f10 * r->f18`.
 */

typedef struct Sub {
    u8  pad00[0x6];
    s16 f06;
    u8  pad08[0x8];
    s16 f10;
    s16 f12;
} Sub;

typedef struct Pad {
    u8  pad00[0x4];
    Sub f04;
} Pad;

typedef struct Rec {
    s16 f00;
    u8  pad02[0x16];
    s16 f18;
} Rec;

typedef struct Dlg {
    u8    pad00[0x5C];
    s32   f5C;
    u8    pad60[0x4];
    u8    f64;
    u8    pad65[0x3];
    void *f68;
    void *f6C;
} Dlg;

extern Pad  *func_28EA40(void *w, s32 id);
extern void  func_28FC90(void *w, s32 id, s32 v, s32 a);
extern Rec  *func_28FE10(void *w, s32 id, s32 a);
extern void  func_28FCD0(void *w, s32 id, s32 v, s32 a);

void factory_FactoryRemoveSelChanged_4fcdd0(Dlg *o)
{
    Sub *b;
    Rec *r;

    if ((o->f64 == 1) || (o->f64 == 2) || (o->f64 == 3)) {
    } else {
        return;
    }
    b = &func_28EA40(o->f6C, 0x8912)->f04;
    if (o->f64 == 1) {
        if (o->f5C == b->f12) {
            return;
        }
        func_28FC90(o->f68, 0x5B, b->f12 * b->f06 + 6, 0);
        o->f5C = b->f12;
    }
    if ((o->f64 == 2) || (o->f64 == 3)) {
        if (o->f5C != b->f10) {
            r = func_28FE10(o->f68, 0x5C, 0);
            func_28FCD0(o->f68, 0x5C, r->f00 + 2 + b->f10 * r->f18, 3);
            o->f5C = b->f10;
        }
    }
}
