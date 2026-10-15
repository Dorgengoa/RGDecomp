#include "types.h"
/* insect 0x0051B580 -- 360 bytes, 90 instructions.
 *
 * Two-arm state dispatch (`beql` into both blocks, so a `switch`, case order
 * 0 then 1 = the compare chain 1, 0 reversed).  The two out-parameter pairs
 * live in separate scopes: retail gives the inner pair the HIGHER stack slots
 * (0x5C/0x58 vs 0x54/0x50), i.e. a nested block allocates above the enclosing
 * one, and inside a group the first-declared local takes the higher address.
 */

typedef struct Ctx {
    u8  pad0000[0x4960];
    u8  f4960[4];                   /* +0x4960 */
} Ctx;

typedef struct Obj {
    u8  pad00[0x4];
    s32 f4;                         /* +0x04 */
} Obj;

extern Ctx *func_31A8D0(void);
extern void insect_InsectBoardFindPiece_4ee190(void *g, s32 e, s32 *px, s32 *py);
extern s32  insect_InsectBattleGetActorSlot_50db40(Ctx *c, s32 k);
extern void insect_InsectPieceClearActionStatus_512ba0(s32 e);
extern s32  insect_InsectPieceCanAct_514920(s32 e);
extern s32  insect_InsectPieceIsTurnDone_5149f0(s32 e);
extern void insect_InsectPieceFaceCell_515590(s32 e, f32 x, f32 y, f32 t);

s32 insect_InsectSeqExecBtlIn_51b580(Obj *o)
{
    s32 a;
    s32 b;
    Ctx *c;
    void *g;
    s32 x2;
    s32 y2;
    s32 x;
    s32 y;

    c = func_31A8D0();
    if (o == 0 || c == 0) {
        return 1;
    }
    a = insect_InsectBattleGetActorSlot_50db40(c, 0);
    b = insect_InsectBattleGetActorSlot_50db40(c, 1);
    g = c->f4960;
    if (a == 0 || b == 0) {
        return 1;
    }
    switch (o->f4) {
    case 0:
        {
            insect_InsectBoardFindPiece_4ee190(g, b, &x, &y);
            insect_InsectPieceFaceCell_515590(a, (f32)x, (f32)y, 4.0f);
            if (insect_InsectPieceCanAct_514920(b) != 0) {
                insect_InsectBoardFindPiece_4ee190(g, a, &x2, &y2);
                insect_InsectPieceFaceCell_515590(b, (f32)x2, (f32)y2, 4.0f);
            }
            o->f4 = o->f4 + 1;
            insect_InsectPieceClearActionStatus_512ba0(a);
            insect_InsectPieceClearActionStatus_512ba0(b);
        }
        break;
    case 1:
        if (insect_InsectPieceIsTurnDone_5149f0(a) != 0 && insect_InsectPieceIsTurnDone_5149f0(b) != 0) {
            return 1;
        }
        break;
    }
    return 0;
}
