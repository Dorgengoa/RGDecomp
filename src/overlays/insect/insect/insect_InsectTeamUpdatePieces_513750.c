#include "types.h"
/* insect 0x00513750 -- 108 bytes, 27 instructions.  Five 0x1E8-byte slots. */

typedef struct Ent {
    u8 pad00[0x1E8];
} Ent;

typedef struct Obj {
    Ent a[5];
} Obj;

extern void insect_InsectPieceUpdate_515a30(Ent *e);
extern void insect_InsectPieceMotionQueueUpdate_514370(Ent *e);

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
