/* rgp:protos */
#define RGP_SELF_insect_InsectCursorSetGetCell_511a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00511a40 -- 80 B / 20 words.  Twin of insect_InsectCursorSetGetCurCell_511a90; the only
 * difference is WHICH lookup supplies the record (00511e60 takes two args,
 * 00511e20 one) and hence which registers the two out-pointers arrive in.
 * $17 = a2 and $16 = a3 here, so the out-pointers are parameters three and four.
 * The adds are `$4 + $3` with $4 loaded first, i.e. f8 + fA and f9 + fB in
 * source order; the destinations are `sw`, so the out-pointers are s32 *.
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

/*rgp*/

void insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *px, s32 *py)
{
    Card *c;

    c = ((Card *)insect_InsectCursorSetFindPage_511e60(a, k));
    *px = c->f8 + c->fA;
    *py = c->f9 + c->fB;
}
