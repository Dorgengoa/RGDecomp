/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogLineClear_51c810 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C810 -- 72 B / 18 words.
 * `sb $0, 0x51($4)` is issued off the INCOMING argument register, before the
 * copy to $16 in the jal delay slot, so the 0x51 clear is statement one.
 * insect_InsectBattleLogLineSetText_51c6f0 is the already-matching clear-then-forward pair
 * (a, b); `daddu $5, $0, $0` is hoisted into the prologue, so b is the
 * constant 0.
 * 0x54 is stored TWICE with the 0x53 store between them -- mwcc does not DSE
 * either, so the duplicate is transcribed literally.
 * The member widths (0x50 s8 / 0x51 u8 / 0x52 u8 / 0x53 s8 / 0x54 s8 /
 * 0x56 s16 / 0x58 s16) are read off the sibling copy routine
 * insect_InsectBattleLogLineCopy_51c670, which loads each of them. */

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

void insect_InsectBattleLogLineClear_51c810(Slot *o)
{
    o->m51 = 0;
    insect_InsectBattleLogLineSetText_51c6f0(o, 0);
    o->m54 = 0;
    o->m53 = 0;
    o->m54 = 0;
    o->m56 = 0;
    o->m58 = -1;
    o->m50 = 0;
}
