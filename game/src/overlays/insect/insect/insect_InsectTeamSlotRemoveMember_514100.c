/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotRemoveMember_514100 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514100 -- 140 bytes, 35 instructions.  Remove one entry from a
 * pair of parallel five-byte tables (t[0..4] and t[5..9]) and compact them. */

/*rgp*/

void insect_InsectTeamSlotRemoveMember_514100(s8 *t, s32 v)
{
    s32 i;
    s32 r;
    s8 *p;

    r = insect_InsectTeamSlotFindMember_513f60(t, v);
    if (r != -1) {
        t[r] = -1;
        t[r + 5] = -1;
    }
    for (i = 0; i < 5; i++) {
        p = t + i;
        if (*p == -1) {
            if (i + 1 < 5) {
                p[0] = p[1];
                p[5] = p[6];
                p[1] = -1;
                p[6] = -1;
            }
        }
    }
}
