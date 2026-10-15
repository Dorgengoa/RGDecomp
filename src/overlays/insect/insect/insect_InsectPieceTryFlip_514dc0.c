#include "types.h"
/* insect 0x00514dc0 -- 100 B / 25 words (three trailing nops are link padding).
 * Three-member family 00514ca0 / 00514dc0 / 00514e30.  The byte written at the
 * end is 0x3C + <index>, i.e. the m3C[7] array already settled by
 * insect_InsectPieceStatsInit_513120.c -- 0x3D/0x3F/0x40 map to indices 1/3/4.
 *
 * `daddu $6,$0,$0` is scheduled ahead of the save area: it is the THIRD
 * argument of insect_InsectPieceGetStat_512e20, hoisted, not a local.  `beql $2,$0` past the
 * arm with `ld $31` in the delay slot is the plain `if (x != 0)` fall-through.
 */

typedef struct Slot {
    u8 pad00[0x3C];
    s8 m3C[7];                  /* +0x3C */
} Slot;

extern s32  insect_InsectPieceGetStat_512e20(Slot *o, s32 a, s32 b);
extern s32  insect_InsectPieceRollVsResist_512bf0(Slot *o, s32 a, s32 b);
extern void insect_InsectPieceSetStatus_5132d0(Slot *o, s32 k);

void insect_InsectPieceTryFlip_514dc0(Slot *o, s32 b)
{
    if (insect_InsectPieceRollVsResist_512bf0(o, insect_InsectPieceGetStat_512e20(o, 4, 0), b) != 0) {
        insect_InsectPieceSetStatus_5132d0(o, 4);
        o->m3C[4] = 3;
    }
}
