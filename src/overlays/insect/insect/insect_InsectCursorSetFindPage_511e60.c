#include "types.h"
/* insect 0x00511E60 -- 20 instructions.  A linear scan of 0x20-byte records
 * terminated by an id of -1; there is no loop bound, so it is a `for (;;)`.
 *
 * `sltu $4,$0,$2` + `xori $4,$4,1` is the BOOLEAN form of the null test --
 * `!p`, not `p == 0` (which would be a bare `beql`).
 *
 * !! THE TWO IN-LOOP EXITS ARE SPELLED DIFFERENTLY ON PURPOSE, and that is
 * the whole match.  Both reach the same trailing `return 0`; retail duplicates
 * the one-word `daddu $2,$0,$0` into the ANNULLED slot of BOTH branch-likelys.
 * Writing both as `break` makes mwcc duplicate for the first and SHARE for the
 * second -- `beq .L00511EA4` + nop, 2 bad words, and that was the floor for
 * three sessions.  Writing both as `return 0` is +3 words.  Only the MIXED
 * spelling below matches.  See levers.d/mwcc-mixed-exit-statements: an N-exit
 * unit has a 2^N exit lattice and a uniform sweep only ever tests 2 cells. */

typedef struct Rec {
    s16 m00;                        /* +0x00 */
    u8  pad02[0x20 - 0x02];
} Rec;

typedef struct Obj {
    u8   pad000[0x8];
    Rec *m08;                       /* +0x08 */
} Obj;

Rec *insect_InsectCursorSetFindPage_511e60(Obj *o, s32 key)
{
    Rec *base;
    Rec *p;
    s32  i;
    s16  v;

    base = o->m08;
    i = 0;
    if (base != 0) {
        for (;;) {
            p = &base[i];
            if ((p != 0) ^ 1) {
                break;
            }
            v = p->m00;
            if (v != -1) {
                if (v == key) {
                    return p;
                }
            } else {
                return 0;
            }
            i++;
        }
    }
    return 0;
}
