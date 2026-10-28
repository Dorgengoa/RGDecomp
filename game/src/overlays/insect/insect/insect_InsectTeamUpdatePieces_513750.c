/* rgp:protos */
#define RGP_SELF_insect_InsectTeamUpdatePieces_513750 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513750 -- 108 bytes, 27 instructions.  Five 0x1E8-byte slots. */

typedef struct Ent {
    u8 pad00[0x1E8];
} Ent;

typedef struct Obj {
    Ent a[5];
} Obj;

/*rgp*/
/*rgp*/

void insect_InsectTeamUpdatePieces_513750(Obj *o)
{
    s32 i;
    Ent *e;

    for (i = 0; i < 5; i++) {
        e = &o->a[i];
        insect_InsectPieceUpdate_515a30(e);
        insect_InsectPieceMotionQueueUpdate_514370(e);
    }
}
