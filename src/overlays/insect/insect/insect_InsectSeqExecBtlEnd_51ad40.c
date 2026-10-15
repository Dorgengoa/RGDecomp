#include "types.h"
/* insect 0x0051AD40 -- 460 bytes, 115 instructions.
 *
 * Same preamble family as insect_FUN_0051B000: the two `||` guards, then a
 * two-arm dispatch on a->f4.  The dispatch's two compares are `beql` INTO the
 * arms, so it is a `switch` and the source case order is the compare chain
 * REVERSED -- case 0 first (block 0x0051ADC4), case 1 second (0x0051AEC4). */

typedef struct Ent {
    u8  pad00[0x1C];
    s16 f1C;                        /* +0x1C */
    u8  pad1E[0x4D - 0x1E];
    s8  f4D;                        /* +0x4D */
    u8  pad4E[0x71 - 0x4E];
    s8  f71;                        /* +0x71 */
} Ent;

typedef struct Host {
    u8  pad00[0x5EF1];
    u8  f5EF1;                      /* +0x5EF1 */
} Host;

typedef struct Ctl {
    u8  pad00[4];
    s32 f4;                         /* +0x4 */
} Ctl;

extern Host *func_31A8D0(void);
extern Ent  *insect_InsectBattleGetActorSlot_50db40(Host *h, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Host *h, s32 k);
extern void  insect_InsectBattleSetFlag_50dad0(Host *h, s32 k);
extern f32   insect_InsectPieceGetHpRatio_512e70(Ent *e);
extern s32   insect_InsectPieceCanAct_514920(Ent *e);
extern s32   insect_InsectPieceIsTurnDone_5149f0(Ent *e);
extern void  insect_InsectPieceSetYawTarget_5156d0(Ent *e, f32 a, f32 b);

s32 insect_InsectSeqExecBtlEnd_51ad40(Ctl *c)
{
    Host *h;
    Ent *p;
    Ent *q;

    h = func_31A8D0();
    if (c == 0 || h == 0) {
        return 1;
    }
    p = insect_InsectBattleGetActorSlot_50db40(h, 0);
    q = insect_InsectBattleGetActorSlot_50db40(h, 1);
    if (p == 0 || q == 0) {
        return 1;
    }
    switch (c->f4) {
    case 0:
        if (p->f71 != h->f5EF1) {
            if (q->f4D == 0) {
                insect_InsectPieceSetYawTarget_5156d0(p, 0.0f, 4.0f);
                if (q->f1C > 0) {
                    insect_InsectPieceSetYawTarget_5156d0(q, 0.0f, 4.0f);
                }
                c->f4++;
            }
        } else {
            if (q->f4D == 0) {
                if (insect_InsectPieceGetHpRatio_512e70(q) <= 0.0f) {
                    insect_InsectPieceSetYawTarget_5156d0(p, 0.0f, 4.0f);
                    insect_InsectBattleSetFlag_50dad0(h, 0x3C);
                    insect_InsectBattleClearFlag_50da90(h, 0x3A);
                } else {
                    if (insect_InsectPieceCanAct_514920(q) != 0) {
                        insect_InsectBattleSetFlag_50dad0(h, 0x3A);
                    } else {
                        insect_InsectBattleClearFlag_50da90(h, 0x3A);
                        insect_InsectPieceSetYawTarget_5156d0(p, 0.0f, 4.0f);
                    }
                }
                c->f4++;
            }
        }
        break;
    case 1:
        if (insect_InsectPieceIsTurnDone_5149f0(p) != 0 && insect_InsectPieceIsTurnDone_5149f0(q) != 0) {
            return 1;
        }
        break;
    }
    return 0;
}
