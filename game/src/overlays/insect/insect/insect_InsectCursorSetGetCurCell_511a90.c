/* rgp:protos */
#define RGP_SELF_insect_InsectCursorSetGetCurCell_511a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00511a90 -- 80 B / 20 words.  Twin of insect_InsectCursorSetGetCell_511a40 with the
 * ONE-argument lookup 00511e20, so the out-pointers slide down to parameters
 * two and three ($17 = a1, $16 = a2).
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

void insect_InsectCursorSetGetCurCell_511a90(void *a, s32 *px, s32 *py)
{
    Card *c;

    c = ((Card *)insect_InsectCursorSetGetCurPage_511e20(a));
    *px = c->f8 + c->fA;
    *py = c->f9 + c->fB;
}
