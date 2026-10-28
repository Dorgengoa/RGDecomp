/* rgp:protos */
#define RGP_SELF_insect_InsectModelMemFindPiece_512370 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512370 -- 132 bytes, 33 instructions.
 *
 * Two nested scans: the outer walks a 0x994-byte block, the inner a 5-entry
 * table of 0x1E8-byte entries returned by insect_InsectTeamGetPiece_5138d0.  The matching
 * entry POINTER is the return value ($2 is never rewritten on the match path,
 * because the `addiu $2,$2,0x1E8` bump sits in the `bnel`'s annulled slot).
 */

typedef struct Ent {
    u8  pad00[0x6C];
    s16 m6C;                        /* +0x6C */
    u8  pad6E[0x1E8 - 0x6E];
} Ent;

typedef struct Ctx {
    u8  pad00[0x438];
    u8 *m438;                       /* +0x438 */
} Ctx;

/*rgp*/

Ent *insect_InsectModelMemFindPiece_512370(Ctx *c, s32 id)
{
    u8  *base;
    s32  k;
    s32  j;
    Ent *p;

    base = c->m438;
    for (k = 0; k < 2; k++) {
        p = ((Ent *)insect_InsectTeamGetPiece_5138d0(base, 0));
        for (j = 0; j < 5; j++) {
            if (id == p->m6C) {
                return p;
            }
            p++;
        }
        base = base + 0x994;
    }
    return 0;
}
