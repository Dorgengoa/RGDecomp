/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePickTurnStartVoiceOffset_4f0130 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F0130 -- 236 bytes.  Counts, for each of two 0x994-byte teams,
 * how many of its five 0x1E8-byte members answer query 0x1B, then turns the
 * two counts plus a random parity into a small signed verdict. */

typedef struct Mem {
    u8 pad0000[0x1E8];
} Mem;

typedef struct Team {
    u8 pad0000[0x994];
} Team;

typedef struct Own {
    u8   pad0000[0x35F8];
    Team f35F8[2];                  /* +0x35F8 */
} Own;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattlePickTurnStartVoiceOffset_4f0130(Own *o)
{
    s32   n[2];
    Team *t;
    s32   j;
    Mem  *m;
    s32   i;
    s32   r;
    s32   v;

    t = &o->f35F8[0];
    for (j = 0; j < 2; j++) {
        n[j] = 0;
        m = ((Mem *)insect_InsectTeamGetPiece_5138d0(t, 0));
        for (i = 0; i < 5; i++) {
            if (insect_InsectPieceTestStatus_513280(m, 0x1B) != 0) {
                n[j]++;
            }
            m++;
        }
        t++;
    }
    r = Rand_133710();
    v = r & 1;
    if (r < 0) {
        if (v != 0) {
            v -= 2;
        }
    }
    if (n[1] < n[0]) {
        if (n[1] < 4) {
            v += 2;
        }
    }
    return v;
}
