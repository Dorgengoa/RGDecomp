/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecSnailBomber_516f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00516F00 -- 540 bytes, 135 instructions.  Phase driver keyed on
 * c->f04; three arms and a default. */

typedef struct Unit { u8 pad[0x1E8]; } Unit;
typedef struct Team { u8 pad[0x994]; } Team;
typedef struct Grid { u8 pad[4]; } Grid;
typedef struct Cell Cell;

typedef struct Obj {
    u8   pad0000[0x35F8];
    Team f35F8[2];                  /* +0x35F8 */
    u8   pad4920[0x4960 - 0x4920];
    Grid f4960;                     /* +0x4960 */
    u8   pad4964[0x5EF1 - 0x4964];
    u8   f5EF1;                     /* +0x5EF1 */
} Obj;

typedef struct Ctl {
    u8  pad00[4];
    s32 f04;                        /* +0x04 */
} Ctl;

typedef struct Hit {
    s32 f00;                        /* +0x00 */
    s32 f04;                        /* +0x04 */
    s32 f08;                        /* +0x08 */
} Hit;

typedef struct Act {
    u8  pad00[0x58];
    s32 f58;                        /* +0x58 */
} Act;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectSeqExecSnailBomber_516f00(Ctl *c)
{
    s32 tx;
    s32 ty;
    Hit st __attribute__((aligned(16)));
    Obj *g;
    Grid *grid;
    Act *h;
    s32 v;
    Cell *cell;
    Unit *u;
    s32 j;
    s32 i;
    s32 k;
    Team *t;

    g = ((Obj *)InsectBattleGet_31a8d0());
    grid = &g->f4960;
    insect_InsectSeqGetActors_51b7e0(&st);
    h = (Act *)st.f00;
    v = st.f08;
    if (h == 0) {
        return 1;
    }
    insect_InsectBoardFindPiece_4ee190(grid, h, &tx, &ty);
    switch (c->f04) {
    case 0:
        insect_InsectBattleSetFlag_50dad0(g, g->f5EF1 + 0x48);
        insect_InsectBattlePlayBankSe_5107d0(0x23);
        c->f04 = c->f04 + 1;
        break;
    case 1:
        for (j = 0; j < 7; j++) {
            for (i = 0; i < 5; i++) {
                if (insect_InsectBoardIsInAttackRange_4ee850(grid, i, j) != 0) {
                    cell = ((Cell *)insect_InsectBoardGetPiece_4ee9a0(grid, i, j));
                    if (cell != 0) {
                        insect_InsectBattleApplyDamage_50f350(h, cell,
                                            insect_InsectBattleSpecialDamage_50fc50(h, cell, v),
                                            v, 0);
                    }
                }
            }
        }
        insect_InsectBattlePieceSetDesignVisible_50fa80(((Act *)insect_InsectBattleGetPieceModel_50df60(g, h)), h, -1);
        c->f04 = c->f04 + 1;
        break;
    case 2:
        t = &g->f35F8[0];
        for (i = 0; i < 2; i++) {
            u = ((Unit *)insect_InsectTeamGetPiece_5138d0(t, 0));
            for (k = 0; k < 5; k++) {
                insect_InsectPieceTestStatus_513280(u, 0x1D);
                u++;
            }
            t++;
        }
        insect_InsectPieceSetStatus_5132d0(h, 0x24);
        insect_InsectPieceSetHp_512ee0(h, 0);
        insect_InsectPieceClearStatus_513340(h, 0x23);
        ModelDetachRootFrames_151460(h->f58);
        return 1;
    }
    return 0;
}
