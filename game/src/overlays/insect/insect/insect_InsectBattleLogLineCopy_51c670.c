/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogLineCopy_51c670 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C670 -- 116 B / 29 words.  The copy sibling of
 * insect_InsectBattleLogLineClear_51c810; same Slot declaration.
 *
 * The forwarded call has a NOP in its delay slot and $4/$5 are untouched
 * since entry, so insect_InsectBattleLogLineSetText_51c6f0(a, b) is called with the ORIGINAL two
 * arguments -- $16/$17 are the copies kept live for the member copies after
 * it.
 * `beqz $16` (not beql) past the whole body: a plain `if (b != 0) { ... }`.
 * The tail `lb 0x50 / sltu $0, $3 / sb 0x50` is a boolean normalisation,
 * i.e. `a->m50 = (b->m50 != 0);`.
 * Copy order is 0x54, 0x51, 0x52, 0x53, 0x56, 0x58, 0x50 -- NOT address
 * order, so these are seven explicit statements, not a struct assignment. */

typedef struct Slot {
    u8  pad00[0x50];
    s8  m50;                    /* +0x50 */
    u8  m51;                    /* +0x51 */
    u8  m52;                    /* +0x52 */
    s8  m53;                    /* +0x53 */
    s8  m54;                    /* +0x54 */
    u8  pad55[1];
    s16 m56;                    /* +0x56 */
    s16 m58;                    /* +0x58 */
} Slot;

/*rgp*/

void insect_InsectBattleLogLineCopy_51c670(Slot *a, Slot *b)
{
    if (b != 0) {
        insect_InsectBattleLogLineSetText_51c6f0(a, b);
        a->m54 = b->m54;
        a->m51 = b->m51;
        a->m52 = b->m52;
        a->m53 = b->m53;
        a->m56 = b->m56;
        a->m58 = b->m58;
        a->m50 = (b->m50 != 0);
    }
}
