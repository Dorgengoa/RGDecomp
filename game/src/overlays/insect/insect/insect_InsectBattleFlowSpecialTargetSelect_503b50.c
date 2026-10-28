/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowSpecialTargetSelect_503b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ins {
    u8    pad000[0x4960];
    u8    f4960[0x4F90 - 0x4960];   /* +0x4960 */
    u8    f4F90[0x2C];              /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x5B24 - 0x4FBD];
    void *f5B24;                    /* +0x5B24 */
    void *f5B28;                    /* +0x5B28 */
    void *f5B2C;                    /* +0x5B2C */
    u8    pad5B30[0x5EE9 - 0x5B30];
    s8    f5EE9;                    /* +0x5EE9 */
    s8    f5EEA;                    /* +0x5EEA */
    u8    pad5EEB[0x5EF1 - 0x5EEB];
    u8    f5EF1;                    /* +0x5EF1 */
} Ins;

typedef struct Q { u8 pad00[0x62]; s8 f62; } Q;
typedef struct Card { u8 pad00[8]; s8 f08; s8 f09; s8 f0A; s8 f0B; } Card;

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
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowSpecialTargetSelect_503b50(Ins *o)
{
    s32   x;
    s32   y;
    s32   ax;
    s32   ay;
    void *h;
    void *t;
    Q    *g;
    void *p;
    void *q;
    Card *c;
    Card *d;
    s32   kind;
    s32   u;
    s32   m;
    s32   r;
    s32   v;
    u8    z;

    h = o->f5B28;
    g = ((Q *)insect_InsectBattleGetSpecialRec_50db30(o));
    t = o->f4960;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBoardFindPiece_4ee190(t, h, &ax, &ay);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0xB, 0);
        insect_InsectCursorSetSetCell_511c50(o->f4F90, ax, ay);
        insect_InsectBattleSetState_50d8c0(o, 0x19, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        v = 0x32;
        if (o->f5EF1 == 1) {
            v = 0x33;
        }
        insect_InsectBattleSetFlag_50dad0(o, v);
        break;
    case 0x1B:
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        insect_InsectBattleSetFlag_50dad0(o, 0x28);
        /* fallthrough */
    case 0x1C:
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x, &y);
        p = insect_InsectBoardGetPiece_4ee9a0(t, x, y);
        z = !o->f5EF1;
        kind = z + 0x32;
        insect_InsectBattleClearFlag_50da90(o, kind);
        if (p != 0) {
            if (insect_InsectPieceIsEnemyOf_5149b0(h, p) == 0) {
                p = 0;
            }
            if (p != 0) {
                insect_InsectBattleSetFlag_50dad0(o, kind);
            }
            o->f5B2C = p;
            o->f5B24 = p;
        }
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0 &&
            insect_InsectBoardIsInAttackRange_4ee850(t, x, y) != 0) {
            q = insect_InsectBoardGetPiece_4ee9a0(t, x, y);
            if (q != 0) {
                if (insect_InsectPieceIsEnemyOf_5149b0(h, q) != 0) {
                    m = 1;
                } else {
                    m = 2;
                }
            } else {
                m = 0;
            }
            switch (g->f62) {
            case 0:
            case 0xB:
            case 0xC:
                r = 0;
                if (insect_InsectBoardGetPiece_4ee9a0(t, x, y) != 0) {
                    r = 1;
                }
                switch (g->f62) {
                case 0:
                    break;
                case 0xB:
                    if (insect_InsectBoardIsHole_4ee7e0(t, x, y) != 0) {
                        r = 1;
                    }
                    break;
                case 0xC:
                    if (insect_InsectBoardIsHole_4ee7e0(t, x, y) == 0) {
                        r = 1;
                    }
                    break;
                }
                if (r != 0) {
                    insect_InsectBattlePlaySe_4f45b0(o, 0x2B);
                } else {
                    o->f5B24 = 0;
                    o->f5B2C = 0;
                    u = y;
                    o->f5EE9 = x;
                    o->f5EEA = u;
                    insect_InsectBattleSetState_50d8c0(o, 0x1A, 0, -1);
                    o->f4FBC = o->f4FBC | 2;
                    insect_InsectBattlePlaySe_4f45b0(o, 5);
                }
                break;
            case 0x10:
                r = 5;
                if (insect_InsectBoardIsHole_4ee7e0(t, x, y) != 0) {
                    r = 0x2B;
                } else {
                    o->f5B24 = 0;
                    o->f5B2C = 0;
                    u = y;
                    o->f5EE9 = x;
                    o->f5EEA = u;
                    insect_InsectBattleSetState_50d8c0(o, 0x1A, 0, -1);
                    o->f4FBC = o->f4FBC | 2;
                }
                insect_InsectBattlePlaySe_4f45b0(o, r);
                break;
            default:
                switch (m) {
                case -1:
                    break;
                case 0:
                    insect_InsectBattlePlaySe_4f45b0(o, 0x2B);
                    break;
                case 1:
                    insect_InsectBattleSetState_50d8c0(o, 0x1A, 0, -1);
                    o->f4FBC = o->f4FBC | 2;
                    break;
                case 2:
                    insect_InsectBattlePlaySe_4f45b0(o, 0x2B);
                    break;
                }
                break;
            }
        }
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x22, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x22, 2, -1);
            insect_InsectBattlePlaySe_4f45b0(o, 6);
        }
        break;
    case 0x22:
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        insect_InsectCursorSetPopPage_511ca0(o->f4F90);
        o->f4FBC = o->f4FBC | 2;
        insect_InsectBattleClearFlag_50da90(o, 0x32);
        insect_InsectBattleClearFlag_50da90(o, 0x33);
        insect_InsectBattleClearFlag_50da90(o, 0x28);
        if (insect_InsectBattleTestFlag_50da40(o, 0x37) != 0) {
            c = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA));
            d = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB));
            d->f08 = c->f08;
            d->f09 = c->f09;
            d->f0A = c->f0A;
            d->f0B = c->f0B;
        } else {
            c = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 2));
            d = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB));
            d->f08 = c->f08;
            d->f09 = c->f09;
            d->f0A = c->f0A;
            d->f0B = c->f0B;
        }
        break;
    case 0x24:
    case 0xA:
    case 0xB:
        break;
    }
}
