#include "types.h"
/* insect 0x005187E0 -- 388 bytes.  A three-phase tutorial step: point at a
 * cell, wait for the tap, then commit the move. */

typedef struct Grid {
    u8 pad0000[0x100];
} Grid;

typedef struct Actor {
    u8 pad0000[0x40];
} Actor;

typedef struct Sys {
    u8   pad0000[0x4960];
    Grid f4960;                     /* +0x4960 */
    u8   pad49A0[0x5178 - 0x4A60];
} Sys;

typedef struct Step {
    u8  pad0000[0x4];
    s32 f4;                         /* +0x04 */
} Step;

extern f32 D_0047DD54;

extern const u8 D_00525338[];

extern Sys   *func_31A8D0(void);
extern Actor *insect_InsectBattleGetActorSlot_50db40(Sys *s, s32 k);
extern s32    insect_InsectBoardFindPiece_4ee190(Grid *g, Actor *a, s32 *px, s32 *py);
extern void   insect_InsectSeqGetTargetCell_51b710(s32 *px, s32 *py);
extern void   insect_InsectPieceFaceCell_515590(Actor *a, f32 x, f32 y, f32 z);
extern s32    insect_InsectPieceIsTurnDone_5149f0(Actor *a);
extern void   insect_InsectPieceMotionQueuePush_514510(Actor *a, const u8 *b, s32 k, f32 x, f32 y);
extern void   insect_InsectBattleEffectsSpawn_51dc30(void *h, Actor *a, s32 a2, s32 a3, s32 a4,
                                  s32 a5, s32 a6, s32 a7, s32 a8);
extern f32    insect_InsectPieceGetMotionPhase_5142d0(Actor *a);
extern void   insect_InsectBoardHoleSet_4ee700(Grid *g, s32 x, s32 y);

s32 insect_InsectSeqExecDig_5187e0(Step *p)
{
    s32    cx;
    s32    cy;
    s32    tx;
    s32    ty;
    Sys   *s;
    Actor *a;
    Grid  *g;
    void  *h;

    s = func_31A8D0();
    if (p == 0 || s == 0) {
        return 1;
    }
    g = &s->f4960;
    a = insect_InsectBattleGetActorSlot_50db40(s, 2);
    if (a == 0) {
        return 1;
    }
    insect_InsectBoardFindPiece_4ee190(g, a, &cx, &cy);
    insect_InsectSeqGetTargetCell_51b710(&tx, &ty);
    h = (u8 *)s + 0x5178;
    switch (p->f4) {
    case 0:
        insect_InsectPieceFaceCell_515590(a, (f32)tx, (f32)ty, 4.0f);
        p->f4 = p->f4 + 1;
        break;
    case 1:
        if (insect_InsectPieceIsTurnDone_5149f0(a) != 0) {
            insect_InsectPieceMotionQueuePush_514510(a, D_00525338, 6, 0.0f, 1.0f);
            insect_InsectBattleEffectsSpawn_51dc30(h, a, 0x1B, 6, 0, -1, -1, 1, 0);
            p->f4 = p->f4 + 1;
        }
        break;
    case 2:
        if (insect_InsectPieceGetMotionPhase_5142d0(a) >= D_0047DD54) {
            insect_InsectBoardHoleSet_4ee700(g, tx, ty);
            return 1;
        }
        break;
    }
    return 0;
}
