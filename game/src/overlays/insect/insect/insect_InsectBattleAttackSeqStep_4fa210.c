/* rgp:protos */
#define RGP_SELF_insect_InsectBattleAttackSeqStep_4fa210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FA210 -- 1128 bytes.  A phase driver: `switch` on
 * insect_InsectBattleGetStep_50d6a0(o, 3) with four constant arms.  The compare chain is
 * emitted in REVERSE source order, so the source runs 1, 6, 0x1C, 0x1D.
 */

typedef struct Ent {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
    u8  pad39[0x58 - 0x39];
    s32 f58;                        /* +0x58 */
    u8  pad5C[0x6C - 0x5C];
    s16 f6C;                        /* +0x6C */
    u8  pad6E[0x71 - 0x6E];
    s8  f71;                        /* +0x71 */
} Ent;

typedef struct Obj {
    u8   pad000[0x870];
    s32  f870;                      /* +0x870 */
    u8   pad874[0x4FBC - 0x874];
    u8   f4FBC;                     /* +0x4FBC */
    u8   pad4FBD[0x5B20 - 0x4FBD];
    Ent *f5B20[4];                  /* +0x5B20 */
    u8   pad5B30[0x5EF1 - 0x5B30];
    u8   f5EF1;                     /* +0x5EF1 */
    u8   pad5EF2[0x5EF8 - 0x5EF2];
    s32  f5EF8;                     /* +0x5EF8 */
    u8   pad5EFC[0x5F82 - 0x5EFC];
    s8   f5F82[0x5FC8 - 0x5F82];    /* +0x5F82 */
    f32  f5FC8;                     /* +0x5FC8 */
} Obj;

extern u8   insect_D_00524DC0[];
extern f32  D_0047DB50;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(s8 *d, u8 *f, s32 v);
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

void insect_InsectBattleAttackSeqStep_4fa210(Obj *o)
{
    Ent *p;
    Ent *a;
    Ent *b;
    s32  h;
    s32  i;
    s32  j;
    s32  dv;
    s32  nn;

    h = ((s32)insect_InsectSeqGet_5108d0());
    a = o->f5B20[0];
    b = o->f5B20[1];
    switch (insect_InsectBattleGetStep_50d6a0(o, 3)) {
    case 1:
        {
            s8 *t;

            o->f4FBC = o->f4FBC | 0x40;
            insect_InsectBattleClearFlag_50da90(o, 0x15);
            insect_InsectBattleClearFlag_50da90(o, 0x27);
            insect_InsectBattleClearFlag_50da90(o, 0x28);
            insect_InsectBattleClearTextBuf_50e120(o, 2);
            t = o->f5F82;
            insect_InsectPieceMotionQueueClear_514320(a);
            Sprintf_1343b8(t, insect_D_00524DC0, a->f38);
            insect_InsectSeqRequestFile_4e9fa0(h, t);
            insect_InsectBattleSetStep_50d7a0(o, 6, 3, -1);
        }
        break;
    case 6:
        if (insect_InsectSeqIsLoadDone_4e9f70(h) != 0) {
            s8 *t;

            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 3, -1);
            if (insect_InsectBattleTestFlag_50da40(o, 0x3B) == 0) {
                insect_InsectBattleCamSave_4f1b50(o);
                insect_InsectBattleSetFlag_50dad0(o, 0x3B);
                o->f5EF8 = 4;
            }
            if (insect_InsectBattleTestFlag_50da40(o, 0x12) == 0) {
                insect_InsectBattleSetFlag_50dad0(o, 0x12);
                insect_InsectBattleClearTextBuf_50e120(o, 2);
                t = o->f5F82;
                Sprintf_1343b8(t, insect_D_00524DC0, b->f38);
                insect_InsectSeqRequestFile_4e9fa0(h, t);
            }
            insect_InsectBattleClearFlag_50da90(o, 0x42);
            for (i = 0; i < 0xA; i++) {
                p = ((Ent *)insect_InsectBattleGetPiece_4f0b90(o, i));
                if (p != a && p != b && insect_InsectPieceIsInPlay_5149e0(p) != 0) {
                    dv = o->f870;
                    ParamTableSetAlpha_1cfb10(dv, p->f6C, D_0047DB50);
                    if (p->f58 != 0) {
                        ParamTableSetAlpha_1cfb10(o->f870, (s16)(p->f6C + 0x40), D_0047DB50);
                    }
                }
            }
        }
        break;
    case 0x1C:
        if (((unsigned char)insect_InsectSeqIsCmdIdle_4e9f80(h)) != 0) {
            if (insect_InsectBattleTestFlag_50da40(o, 0x3A) != 0) {
                insect_InsectBattleClearFlag_50da90(o, 0x3A);
                o->f5B20[0] = b;
                o->f5B20[1] = a;
                insect_InsectBattleSetStep_50d7a0(o, 6, 3, -1);
            } else {
                insect_InsectBattleClearFlag_50da90(o, 0x12);
                insect_InsectSeqLoadRelease_4e9f00(h);
                if (insect_InsectBattleTestFlag_50da40(o, 0x3C) != 0) {
                    insect_InsectBattleClearFlag_50da90(o, 0x3C);
                    insect_InsectPieceSetStatus_5132d0(a, 0x1C);
                } else if (o->f5EF1 == a->f71) {
                    insect_InsectPieceSetStatus_5132d0(a, 0x1C);
                } else {
                    insect_InsectPieceSetStatus_5132d0(b, 0x1C);
                }
                if (insect_InsectBattleIsSideAi_4f1950(o, o->f5EF1) == 0) {
                    insect_InsectBattleSetState_50d8c0(o, 0x15, 0, -1);
                }
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 3, -1);
                insect_InsectBattleClearFlag_50da90(o, 0x3B);
            }
        }
        break;
    case 0x1D:
        for (i = 0; i < 0xA; i++) {
            b = ((Ent *)insect_InsectBattleGetPiece_4f0b90(o, i));
            if (insect_InsectPieceIsInPlay_5149e0(b) != 0) {
                nn = (s32)(15.0f / o->f5FC8);
                ParamTableFadeToOne_1cf9e0(o->f870, b->f6C, nn);
                if (b->f58 != 0) {
                    ParamTableFadeToOne_1cf9e0(o->f870, (s16)(b->f6C + 0x40),
                                (s32)(15.0f / o->f5FC8));
                }
            }
        }
        o->f5EF8 = 0xB;
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 3, -1);
        insect_InsectBattleSetState_50d8c0(o, 1, 5, -1);
        for (j = 0; j < 4; j++) {
            o->f5B20[j] = 0;
        }
        insect_InsectBattleClearFlag_50da90(o, 0x32);
        insect_InsectBattleClearFlag_50da90(o, 0x33);
        insect_InsectBattleClearFlag_50da90(o, 0x28);
        break;
    }
}
