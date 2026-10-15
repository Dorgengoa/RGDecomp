#include "types.h"
/* insect 0x00511b80 -- 72 B / 18 words (three trailing nops are link padding).
 * Twin pair 00511ae0 / 00511b80: the same clamp over a DIFFERENT pair of byte
 * fields (0xE/0xF against 0xA/0xB here vs 0xC/0xD against 0x8/0x9).
 *
 * Parameter one is never touched -- the record is a1.  Each store is followed by
 * a RELOAD of the same byte (`sb $6,0xE` then `lb $4,0xE`), so the compares are
 * written against the MEMBER, not against the parameter.  The second `lb` is
 * duplicated into the beql delay slot, which is the if-body fall-through.
 */

typedef struct Card {
    u8 pad00[8];
    s8 f8;                      /* +0x08 */
    s8 f9;                      /* +0x09 */
    s8 fA;                      /* +0x0A */
    s8 fB;                      /* +0x0B */
    s8 fC;                      /* +0x0C */
    s8 fD;                      /* +0x0D */
    s8 fE;                      /* +0x0E */
    s8 fF;                      /* +0x0F */
} Card;

void insect_InsectCursorSetPageSetSize_511b80(void *a, Card *c, s32 w, s32 h)
{
    if (c != 0) {
        c->fC = w;
        c->fD = h;
        if (c->fC < c->f8) {
            c->f8 = c->fC;
        }
        if (c->fD < c->f9) {
            c->f9 = c->fD;
        }
    }
}
