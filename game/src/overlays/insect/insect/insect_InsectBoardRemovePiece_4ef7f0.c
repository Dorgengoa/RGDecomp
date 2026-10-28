/* rgp:protos */
#define RGP_SELF_insect_InsectBoardRemovePiece_4ef7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EF7F0 -- 60 bytes.  Two out-parameters at $29+0x2C and $29+0x28,
 * FOUR bytes apart, so each is a full word local; the reads are `lh` because
 * only the low halfword is wanted -- an (s16) cast of a word local, not an s16
 * local (two s16 locals pack at 0x2C/0x2E and are two words wrong).
 * Stack locals go in REVERSE declaration order, so the +0x2C one is first. */
/*rgp*/
/*rgp*/

void insect_InsectBoardRemovePiece_4ef7f0(void *o, s32 b)
{
    s32 x;
    s32 y;

    insect_InsectBoardFindPiece_4ee190(o, b, &x, &y);
    insect_InsectBoardTakeAt_4ef770(o, (s16)x, (s16)y);
}
