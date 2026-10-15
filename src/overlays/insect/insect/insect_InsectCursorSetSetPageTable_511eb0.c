#include "types.h"
/* insect 0x00511EB0 -- pass-28 unnamed-listing conversion.  A 0x20-byte
 * record walk terminated by a -1 halfword at +0x00.  ⚠ The inner test is
 * `beql $5, $0` -- the loop clears the four bytes at +0x08..+0x0B only when
 * the cursor is non-null, and the advance sits in that branch-likely's delay
 * slot, so the null arm skips the stores and still advances.  The store order
 * 9, 8, B, A is the listing's and is kept as source order. */
typedef struct Rec {
    s16 m0;            /* +0x00 */
    u8 pad02[0x8 - 0x2];
    u8 m8;             /* +0x08 */
    u8 m9;             /* +0x09 */
    u8 mA;             /* +0x0A */
    u8 mB;             /* +0x0B */
    u8 padC[0x20 - 0xC];
} Rec;

typedef struct Owner {
    u8 pad00[0x8];
    Rec *m8;           /* +0x08 */
} Owner;

void insect_InsectCursorSetSetPageTable_511eb0(Owner *o, Rec *p)
{
    o->m8 = p;
    for (;;) {
        if (p->m0 == -1) {
            break;
        }
        if (p != 0) {
            p->m9 = 0;
            p->m8 = 0;
            p->mB = 0;
            p->mA = 0;
        }
        p += 1;
    }
}
