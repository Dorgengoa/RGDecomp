/* rgp:protos */
#define RGP_SELF_insect_InsectBattleSpecialSeqStep_4f9d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F9D90 -- 1,144 bytes, 288 instructions, 40 calls, 31 conditional
 * branches.  Another insect_InsectBattleGetStep_50d6a0(o, 3) state dispatch.
 *
 * Compare chain 0x1D, 0x1C, 6, 1 -- REVERSED -- block addresses 0x4F9E4C (1),
 * 0x4FA07C (6), 0x4FA0A8 (0x1C), 0x4FA12C (0x1D) run in that order forwards,
 * so the source case order is 1, 6, 0x1C, 0x1D.
 *
 * o->f5B20[4] is ONE array member: the tail loop clears 0x5B20..0x5B2C with
 * `sll/addu/sw 0x5B20($2)` while the body names 0x5B20/0x5B24/0x5B28/0x5B2C
 * individually ([[insect-struct-overlap-declaration]]).
 *
 * The ten-way test on e->f62 is an `||` JOIN, not a switch: the FIRST test is a
 * `beql` carrying the taken arm's own `lw $2,0x5B28($21)`, the other nine are
 * plain `beq`/nop -- ROUND3's `||` shape exactly.
 */

typedef struct Ent {
    u8  pad00[0x1C];
    s16 f1C;                        /* +0x1C */
    u8  pad1E[0x30 - 0x1E];
    u8  f30[0x62 - 0x30];           /* +0x30 */
    s8  f62;                        /* +0x62 */
} Ent;

typedef struct Ins {
    u8   pad000[0x35F8];
    u8   arr[2][0x994];             /* +0x35F8 */
    u8   pad4920[0x4960 - 0x4920];
    u8   f4960[0x5B20 - 0x4960];    /* +0x4960 */
    Ent *f5B20[4];                  /* +0x5B20 */
    u8   pad5B30[0x5EF1 - 0x5B30];
    u8   f5EF1;                     /* +0x5EF1 */
    u8   pad5EF2[0x5F82 - 0x5EF2];
    u8   f5F82[0x40];               /* +0x5F82 */
} Ins;

extern u8 insect_D_00524DB8[];

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
/*rgp*/
/*rgp*/
/*rgp*/
extern void  Sprintf_1343b8(void *dst, const u8 *fmt, u8 *a);

void insect_InsectBattleSpecialSeqStep_4f9d90(Ins *o)
{
    s32   xBC;
    s32   xB8;
    s32   xB4;
    s32   xB0;
    void *p;
    void *q;
    Ent  *w;
    Ent  *e;
    Ent  *s;
    void *g;
    Ent  *b;
    s32   i;
    s32   j;
    Ent  *r;
    u8   *buf;
    s32   m;
    s32   k;

    p = insect_InsectSeqGet_5108d0();
    e = ((Ent *)insect_InsectBattleGetSpecialRec_50db30(o));
    w = o->f5B20[0];
    if (e == 0) {
        if (insect_InsectBattleGetStep_50d6a0(o, 3) != 0xB) {
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 3, -1);
        }
    }
    switch (insect_InsectBattleGetStep_50d6a0(o, 3)) {
    case 1:
        insect_InsectBattleClearFlag_50da90(o, 0x15);
        insect_InsectBattleClearFlag_50da90(o, 0x27);
        insect_InsectBattleClearFlag_50da90(o, 0x28);
        insect_InsectPieceUseSpecialCharge_512c80(w);
        insect_InsectBattleClearFlag_50da90(o, 0x23);
        m = e->f62;
        switch (m) {
        case 0:
        case 6:
        case 0xD:
        case 3:
        case 0xB:
        case 0xC:
        case 7:
        case 0xE:
        case 0xF:
        case 0x10:
            o->f5B20[0] = o->f5B20[2];
            o->f5B20[1] = 0;
            o->f5B20[3] = o->f5B20[2];
            insect_InsectBattleClearFlag_50da90(o, 0x32);
            insect_InsectBattleClearFlag_50da90(o, 0x33);
            break;
        default:
            insect_InsectBattleSetFlag_50dad0(o, 0x32);
            insect_InsectBattleSetFlag_50dad0(o, 0x33);
            break;
        }
        if (m == 7) {
            s = o->f5B20[2];
            g = o->f4960;
            insect_InsectBoardFindPiece_4ee190(g, s, &xBC, &xB8);
            insect_InsectBoardCalcAttackRange_4ec720(g, e, s, xBC, xB8);
            i = 0;
            do {
                q = o->arr[i];
                j = 0;
                while (j < 5) {
                    r = ((Ent *)insect_InsectTeamGetPiece_5138d0(q, j));
                    if (r != 0) {
                        if (insect_InsectPieceIsEnemyOf_5149b0(s, r) != 0) {
                            insect_InsectBoardFindPiece_4ee190(g, r, &xB4, &xB0);
                            if (insect_InsectBoardIsInAttackRange_4ee850(g, xB4, xB0) != 0) {
                                o->f5B20[3] = r;
                                o->f5B20[1] = r;
                                break;
                            }
                        }
                    }
                    j++;
                }
                i++;
            } while (i < 2);
        }
        insect_InsectBattleClearTextBuf_50e120(o, 2);
        buf = o->f5F82;
        insect_InsectPieceMotionQueueClear_514320(w);
        Sprintf_1343b8(buf, insect_D_00524DB8, e->f30);
        insect_InsectSeqRequestFile_4e9fa0(p, buf);
        insect_InsectBattleSetStep_50d7a0(o, 6, 3, -1);
        break;
    case 6:
        if (insect_InsectSeqIsLoadDone_4e9f70(p) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 3, -1);
        }
        break;
    case 0x1C:
        if (((unsigned char)insect_InsectSeqIsCmdIdle_4e9f80(p)) != 0) {
            b = o->f5B20[0];
            r = o->f5B20[1];
            if (b != 0) {
                if (insect_InsectPieceIsInPlay_5149e0(b) != 0) {
                    insect_InsectPieceSetYawTarget_5156d0(b, 0.0f, 4.0f);
                }
            }
            if (r != 0) {
                if (r->f1C > 0) {
                    insect_InsectPieceSetYawTarget_5156d0(r, 0.0f, 4.0f);
                }
            }
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 3, -1);
        }
        break;
    case 0x1D:
        insect_InsectBattleClearFlag_50da90(o, 0x3C);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 3, -1);
        insect_InsectBattleSetState_50d8c0(o, 1, 5, -1);
        if (insect_InsectBattleIsSideAi_4f1950(o, o->f5EF1) == 0) {
            insect_InsectBattleSetState_50d8c0(o, 0x15, 0, -1);
        }
        if (o->f5B20[0] != 0) {
            insect_InsectPieceSetStatus_5132d0(o->f5B20[0], 0x1C);
        }
        o->f5B20[0] = 0;
        o->f5B20[1] = 0;
        k = 0;
        do {
            o->f5B20[k] = 0;
            k++;
        } while (k < 4);
        insect_InsectBattleClearFlag_50da90(o, 0x32);
        insect_InsectBattleClearFlag_50da90(o, 0x33);
        break;
    }
}
