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

extern Obj *func_31A8D0(void);
extern void insect_InsectSeqGetActors_51b7e0(Hit *h, s32 a, s32 b);
extern void insect_InsectBoardFindPiece_4ee190(Grid *g, Act *a, s32 *px, s32 *py);
extern void insect_InsectBattleSetFlag_50dad0(Obj *o, s32 k);
extern void insect_InsectBattlePlayBankSe_5107d0(s32 k);
extern s32 insect_InsectBoardIsInAttackRange_4ee850(Grid *g, s32 x, s32 y);
extern Cell *insect_InsectBoardGetPiece_4ee9a0(Grid *g, s16 x, s16 y);
extern s32 insect_InsectBattleSpecialDamage_50fc50(Act *a, Cell *c, s32 v);
extern void insect_InsectBattleApplyDamage_50f350(Act *a, Cell *c, s32 d, s32 v, s32 z);
extern Act *insect_InsectBattleGetPieceModel_50df60(Obj *o, Act *a);
extern void insect_InsectBattlePieceSetDesignVisible_50fa80(Act *p, Act *a, s32 k);
extern Unit *insect_InsectTeamGetPiece_5138d0(Team *t, s32 k);
extern void insect_InsectPieceTestStatus_513280(Unit *u, s32 k);
extern void insect_InsectPieceSetStatus_5132d0(Act *a, s32 k);
extern void insect_InsectPieceSetHp_512ee0(Act *a, s32 k);
extern void insect_InsectPieceClearStatus_513340(Act *a, s32 k);
extern void func_151460(s32 h);

s32 insect_InsectSeqExecSnailBomber_516f00(Ctl *c)
{
    s32 tx;
    s32 ty;
    Hit st;
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

    g = func_31A8D0();
    grid = &g->f4960;
    insect_InsectSeqGetActors_51b7e0(&st, 2, 1);
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
                    cell = insect_InsectBoardGetPiece_4ee9a0(grid, i, j);
                    if (cell != 0) {
                        insect_InsectBattleApplyDamage_50f350(h, cell,
                                            insect_InsectBattleSpecialDamage_50fc50(h, cell, v),
                                            v, 0);
                    }
                }
            }
        }
        insect_InsectBattlePieceSetDesignVisible_50fa80(insect_InsectBattleGetPieceModel_50df60(g, h), h, -1);
        c->f04 = c->f04 + 1;
        break;
    case 2:
        t = &g->f35F8[0];
        for (i = 0; i < 2; i++) {
            u = insect_InsectTeamGetPiece_5138d0(t, 0);
            for (k = 0; k < 5; k++) {
                insect_InsectPieceTestStatus_513280(u, 0x1D);
                u++;
            }
            t++;
        }
        insect_InsectPieceSetStatus_5132d0(h, 0x24);
        insect_InsectPieceSetHp_512ee0(h, 0);
        insect_InsectPieceClearStatus_513340(h, 0x23);
        func_151460(h->f58);
        return 1;
    }
    return 0;
}
