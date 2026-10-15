#include "types.h"
/* insect 0x00514EA0 -- 100 bytes, 25 instructions.  The third argument of the
 * FIRST call is materialised at the very top of the prologue, which is the
 * tell that its result feeds the second call as a nested expression. */

typedef struct Obj {
    u8 pad00[0x3C];
    s8 f3C;                         /* +0x3C */
} Obj;

extern s32 insect_InsectPieceGetStat_512e20(Obj *o, s32 a, s32 b);
extern s32 insect_InsectPieceRollVsResist_512bf0(Obj *o, s32 a, s32 b);
extern void insect_InsectPieceSetStatus_5132d0(Obj *o, s32 a);

void insect_InsectPieceTryPoison_514ea0(Obj *o, s32 k)
{
    if (insect_InsectPieceRollVsResist_512bf0(o, insect_InsectPieceGetStat_512e20(o, 5, 0), k) != 0) {
        insect_InsectPieceSetStatus_5132d0(o, 0);
        o->f3C = 3;
    }
}
