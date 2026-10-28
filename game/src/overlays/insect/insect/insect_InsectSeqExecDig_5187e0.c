/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecDig_5187e0 1
#include "port/game_protos.h"
#line 1
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

extern u8 insect_D_00525338[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/

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

    s = ((Sys *)InsectBattleGet_31a8d0());
    if (p == 0 || s == 0) {
        return 1;
    }
    g = &s->f4960;
    a = ((Actor *)insect_InsectBattleGetActorSlot_50db40(s, 2));
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
        if (((unsigned char)insect_InsectPieceIsTurnDone_5149f0(a)) != 0) {
            insect_InsectPieceMotionQueuePush_514510(a, insect_D_00525338, 6, 0.0f, 1.0f);
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
