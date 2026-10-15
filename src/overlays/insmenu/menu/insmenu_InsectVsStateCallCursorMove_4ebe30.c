#include "types.h"

/* insmenu 0x004EBE30 (144 bytes, 36 instructions) -- forward a panel event to
 * the current record's handler.
 *
 * ★ EIGHT integer arguments in $4..$11 with nothing on the stack: that is the
 * PS2 EABI's full register set, not a spill (see the argument-ABI note).  The
 * six `addiu $rN, $29, K` before the first call are six out-parameters, and
 * the six `lw $rN, K($29)` after it read the same slots back.
 *
 * ★ `addiu $3, $0, 0x1` sits in a PLAIN branch's delay slot, so it runs on
 * both paths -- it is the initialiser of the result flag, not part of the
 * taken arm.  `andi $3, $2, 0xFF` makes the handler's return u8 and the
 * closing `sltu $2, $0, $3` is `return ok != 0;`.
 *
 * ★ The two guards branch to 0x004EBEA0 and 0x004EBEA4 -- the same join with
 * and without the `ld $31` -- which is the epilogue-merge form of nested ifs,
 * not a single `&&`.
 */

typedef u8 (*Handler)(void *a, void *b, s32 p0, s32 p1, s32 p2, s32 p3,
                      s32 p4, s32 p5);

typedef struct Rec {
    u8 pad00[0x10];
    Handler f10;
} Rec;

extern Rec *insmenu_InsectVsStateRowFind_4ec020(s32 *a, s32 *b, s32 *c, s32 *d, s32 *e,
                                 s32 *f);

s32 insmenu_InsectVsStateCallCursorMove_4ebe30(void *a, void *b)
{
    s32 v0, v1, v2, v3, v4, v5;
    Rec *r;
    s32 ok;

    r = insmenu_InsectVsStateRowFind_4ec020(&v0, &v1, &v2, &v3, &v4, &v5);
    ok = 1;
    if (r != 0) {
        if (r->f10 != 0) {
            ok = r->f10(a, b, v0, v1, v2, v3, v4, v5);
        }
    }
    return ok != 0;
}
