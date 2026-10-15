/* INSECT 0x0051F500: 10,764 bytes / 2,691 words.
 * Byte-exact candidate from the isolated 01a0ac8e continuation.
 * Locals intentionally distinguish lifetimes across switch cases. Their
 * sharing and declaration order reproduce the original register allocation.
 * Case 27 uses an unsigned row index at the write to preserve both retail
 * address calculations. Case 33's final return preserves its shared exit.
 * Independently rebuild this file before integrating it into a shared tree.
 */
#include "types.h"
#pragma divbyzerocheck on
#pragma opt_dead_assignments off

typedef struct Ent  Ent;
typedef struct Cell Cell;
typedef struct Cmd  Cmd;
typedef struct Cfg  Cfg;
typedef struct Ins  Ins;

struct Ent {
    u8  pad00[0x18];
    s8  f18;                        
    u8  pad19;
    s16 f1A;                        
    u8  pad1C[0x26 - 0x1C];
    u8  f26;                        
    u8  pad27;
    u8  f28;                        
    u8  pad29[0x38 - 0x29];
    s8  f38;                        
    s8  f39;                        
    u8  pad3A[0x4F - 0x3A];
    s8  f4F;                        
    u8  pad50[0x71 - 0x50];
    s8  f71;                        
};

struct Cell {
    u8  pad00[0x62];
    s8  f62;                        
};

struct Cmd {
    Ent  *f00;                      
    Ent  *f04;                      
    Ent  *f08;                      
    Cell *f0C;                      
    s8    f10, f11, f12, f13;       
    s8    f14;                      
    u8    pad15;
    s16   f16;                      
    s16   f18;                      
    s8    f1A, f1B, f1C;            
};

struct Cfg {
    s8  f00;                        
    s8  f01;                        
    s8  f02;                        
    u8  f03;                        
    u8  f04;                        
    u8  pad05[3];
    u64 f08;                        
};

struct Ins {
    u8    pad000[0x48];
    Ent  *f48;                      
    Ent  *f4C;                      
    void *f50;                      
    void *f54;                      
    void *f58;                      
    void *f5C;                      
    void *f60;                      
    u8    pad064[0x6C - 0x64];
    s32   f6C;                      
    s32   f70;                      
    s16   f74[10];                  
    u8    pad088[0x94 - 0x88];
    Cell *f94[(0xC4 - 0x94) / 4];   
    u8    fC4[0x8CC - 0xC4];        
    Cmd  *f8CC;                     
    s32   f8D0;                     
    u8    pad8D4[0x8DC - 0x8D4];
    Ent  *f8DC[2][10];              
    Ent  *f92C;                     
    s8    f930;                     
};

extern s16 D_004851BC;              
extern s16 D_004851C0;              
extern u64 D_004851D0;              
extern s8  D_004851E0;              
extern f32 D_0047DADC;              
extern f32 D_0047D344;              
extern const u8 D_00526030[];
extern u8 D_00526040[];
extern u8 D_00526041[];
extern u8 D_00526044[];

extern s32   func_133710(void);
extern void *func_1FEDE0(void);
extern s32   func_3CCAC0(void *h, s32 k);

extern s32   insect_InsectBoardCanMoveAndHit_4ec4a0(void *w, Ent *e, Ent *t, s32 x, s32 y);
extern void  insect_InsectBoardCalcMoveRange_4ed180(void *w, Ent *e);
extern void  insect_InsectBoardPickMoveCell_4edd90(void *w, Ent *e, Ent *t, s32 *x, s32 *y, s32 f);
extern s32   insect_InsectBoardNearestTargetDist_4ede60(void *w, Ent *t, s32 k);
extern Ent  *insect_InsectBoardPickNearer_4edf10(void *w, Ent *e, Ent *a, Ent *b);
extern Ent  *insect_InsectBoardFindNearestTarget_4ee000(void *w, Ent *t, s32 k);
extern void  insect_InsectBoardFindPiece_4ee190(void *w, Ent *e, s32 *x, s32 *y);
extern s32   insect_InsectBoardIsMovable_4ee930(void *w, s32 b, s32 a);
extern s32   insect_InsectBoardAbilityCanHit_4eea10(void *w, Ent *e, Ent *t, Cell *c, s32 *x, s32 *y,
                                 s32 *u, s32 *v, s64 p, s64 q);
extern Ent  *insect_InsectBoardAbilityFindTarget_4ef0f0(void *w, Ent *e, Cell *c, s32 x, s32 y,
                                 s32 *u, s32 *v, Ent *p);
extern s32   insect_InsectBoardAbilityInRange_4ef5e0(void *w, Ent *e, Ent *t, Cell *c, s32 x, s32 y);
extern void  insect_InsectBoardClearMoveMarks_4efa70(void *w);
extern s32   insect_InsectBattleSimExchangeMaybe_50f150(Ent *e, Ent *t, s32 k);
extern f32   insect_InsectPieceGetHpRatio_512e70(Ent *e);
extern s32   insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern void  insect_InsectPieceClearStatus_513340(Ent *e, s32 k);
extern s32   insect_InsectTeamFindKing_513840(void *a);
extern Ent  *insect_InsectTeamGetPiece_5138d0(void *a, s32 i);
extern s32   insect_InsectPieceHasActed_5148f0(Ent *e);
extern s32   insect_InsectPieceIsEnemyOf_5149b0(Ent *a, Ent *b);
extern s32   insect_InsectPieceIsInPlay_5149e0(Ent *e);
extern s32   insect_InsectPieceIsKing_514b00(Ent *e);
extern s32   insect_InsectAbilityTableFilter_51d020(void *m, s32 a, s32 b, s32 c, Cell **out);
extern Ent  *insect_InsectAiSpecialTargetScissorThrow_51e150(Ins *o, Ent *e, Cell *c, s32 b, s32 a);
extern Ent  *insect_InsectAiSpecialTargetCannonBlast_51e3c0(Ins *o, Ent *e, Cell *c, s32 b, s32 a);
extern Ent  *insect_InsectAiSpecialTargetCharmBeam_51e560(Ins *o, Ent *e, Cell *c, s32 b, s32 a, s32 f, Ent *p);
extern Ent  *insect_InsectAiSpecialTargetEmperorsRage_51e8f0(Ins *o, Ent *e, Cell *c, s32 b, s32 a, s32 f, Ent *p);
extern Ent  *insect_InsectAiSpecialTargetBerserker_51ed80(Ins *o, Ent *e, Cell *c, s32 b, s32 a, s32 f, Ent *p);
extern void  insect_InsectAiPlanScissorThrow_51f1d0(Ins *o, s32 k);
extern s32   insect_InsectAiGetEnemySide_521f10(Ins *o);
extern s32   insect_InsectAiAddAttackActions_521f20(Ins *o, Ent *e, s32 x, s32 y);
extern void  insect_InsectAiRankInsert_522110(Ins *o, Ent *e, s32 k, s32 s, s32 t);
extern s32   insect_InsectAiSpecialCanHit_522310(Ins *o, Ent *e, Ent *t, Cell *c, s32 *x, s32 *y);
extern void  insect_InsectAiPickCoverCellMaybe_5224c0(Ins *o, Ent *e, s32 *x, s32 *y);
extern Ent  *insect_InsectAiFindKing_522860(Ins *o, s32 k);
extern Ent  *insect_InsectAiGetPiece_5228f0(Ins *o, s32 i);
extern void  insect_InsectAiPushStep_522930(Ins *o, s32 k);
extern s32   insect_InsectAiGetStep_5229a0(Ins *o);
extern void  insect_InsectAiPushState_5229e0(Ins *o, s32 k);
extern s32   insect_InsectAiRandChance_522b60(Ins *o, u8 k);
extern Cfg  *insect_InsectAiCfgSelectLevel_522d30(void *a, s32 b);
extern void  insect_InsectAiLevelCopy_522e50(Cfg *g, Cfg *r);
extern void  insect_InsectAiActionListReset_523290(void *p);
extern Cmd  *insect_InsectAiActionListGet_5232c0(void *p, s32 i);
extern s32   insect_InsectAiActionListCount_5232d0(void *p);
extern void  insect_InsectAiActionListAdd_5232e0(void *p, Cmd *c);
extern Cmd  *insect_InsectAiActionNew_523330(void *p);
extern void  insect_InsectAiActionListSetHeap_5233a0(void *p, s32 n);
extern void  insect_InsectAiActionListInit_5233b0(void *p);
extern void  insect_InsectAiActionReset_523410(const u8 *t);
extern void  insect_InsectAiActionCtor_523460(const u8 *t);
extern s32   insect_InsectPieceCanActThunk_514920(Ent *e);

void insect_InsectAiThinkStep_51f500(Ins *o, s32 arg1)
{
    s32   sp1BC, sp1B8;
    s32   sp1B4, sp1B0;
    s32   sp1AC, sp1A8;
    s32   sp1A4, sp1A0;
    s32   sp19C, sp198;
    s32   sp194, sp190;
    s32   sp18C, sp188;
    s32   sp184, sp180;
    s32   sp17C, sp178, sp174, sp170;
    s32   sp16C, sp168, sp164, sp160;
    s32   sp15C, sp158, sp154, sp150, sp14C, sp148;
    s32   sp144, sp140, sp13C, sp138;
    s32   sp134, sp130, sp12C, sp128;
    s32   sp124, sp120, sp11C, sp118;
    s32   sp114, sp110, sp10C, sp108, sp104, sp100;
    s32   spFC, spF8, spF4, spF0;
    s32   spE0, spDC;
    f32   d1, d0;
    Ent *ent_case31;
    s32 flg_case39;
    Ent *tgt_case33;
    Ent *ent_case41;
    Ent *ent_case40;
    Ent *ent_case38;
    Ent *ent_case36;
    Ent *tgt_case46;
    Ent *tgt_case45;
    Ent *ent_case37;
    Ent *ent_case39;
    Cell *cell_case46;
    Cell *cell_case37;
    Cell *cell_case33;
    Ent *sub_case37;
    Cell *cell_case36;
    Ent *tgt_case32;
    Cmd *cmd45_second;
    s32 i_case43;
    Ent *tgt_case43;
    Cell *cel2_case41;
    Cfg  *cfg;
    Cfg  *rec;
    Cmd  *cmd;
    Cmd  *cm2;
    Ent  *ent;
    Ent  *tgt;
    Ent  *sub;
    Ent *best32;
    Ent  *best;
    Cell *cell;
    Cell *cel2;
    void *pool;
    s32   bit, flg, ok, n, m, i, j, a, b, k, cnt, kind;

    if (D_004851E0 == 0) {
        insect_InsectAiActionCtor_523460(D_00526030);
        D_004851E0 = 1;
    }
    pool = o->f60;
    rec = insect_InsectAiCfgSelectLevel_522d30(pool, o->f8D0);
    if (rec == 0) {
        rec = insect_InsectAiCfgSelectLevel_522d30(pool, 0);
    }
    if (rec == 0 || o->f5C == 0) {
        insect_InsectAiPushStep_522930(o, 0x2E);
    }
    best = 0;
    cfg = (Cfg *)&D_004851D0;
    bit = rec->f08 & 0x8000;
    if (++D_004851C0 >= 0x258) {
        insect_InsectAiPushStep_522930(o, 0x2D);
    }

    switch (insect_InsectAiGetStep_5229a0(o)) {
    case 26:
        o->f6C = 0;
        insect_InsectAiActionListInit_5233b0(o->fC4);
        insect_InsectAiActionListSetHeap_5233a0(o->fC4, o->f70);
        insect_InsectAiActionListReset_523290(o->fC4);
        for (i = 0; i < 10; i++) {
            o->f74[i] = 0;
            o->f8DC[0][i] = 0;
            o->f8DC[1][i] = 0;
        }
        insect_InsectAiPushStep_522930(o, 0x1B);
        insect_InsectBoardClearMoveMarks_4efa70(o->f58);
        o->f8CC = 0;
        o->f48 = 0;
        o->f4C = 0;
        break;

    case 27:
        k = func_133710() % 5;
        if (rec != 0) {
            k = rec->f00;
        }
        for (i = 0; i < 10; i++) {
            if (i >= 5) {
                ent = insect_InsectTeamGetPiece_5138d0(o->f54, i % 5);
            } else {
                ent = insect_InsectTeamGetPiece_5138d0(o->f50, i);
            }
            if (ent != 0) {
                if (insect_InsectPieceCanActThunk_514920(ent) != 0 && ent->f71 == o->f930 &&
                    insect_InsectPieceIsKing_514b00(ent) == 0) {
                    insect_InsectAiRankInsert_522110(o, ent, k, o->f930, rec->f01);
                }
            }
        }
        for (j = 0; j < 10; j++) {
            m = o->f930;
            if (o->f8DC[m][j] == 0) {

                o->f8DC[(u32)m][j] =
                    insect_InsectAiFindKing_522860(o, m);
                break;
            }
        }
        insect_InsectAiPushStep_522930(o, 0x1C);
        break;

    case 28:
        insect_InsectAiPushStep_522930(o, 0x1D);
        break;

    case 29:
        D_004851C0 = 0;
        D_004851BC = 0;
        insect_InsectAiActionListInit_5233b0(o->fC4);
        insect_InsectAiActionListSetHeap_5233a0(o->fC4, o->f70);
        insect_InsectAiActionListReset_523290(o->fC4);
        insect_InsectAiLevelCopy_522e50(cfg, rec);
        o->f92C = 0;
        for (i = 0; i < 10; i++) {
            ent = o->f8DC[o->f930][i];
            if (ent != 0) {
                if (insect_InsectPieceCanActThunk_514920(ent) != 0 && ent->f71 == o->f930 &&
                    insect_InsectPieceHasActed_5148f0(ent) == 0) {
                    o->f92C = ent;
                    break;
                }
                o->f8DC[o->f930][i] = 0;
            }
        }
        n = 0;
        if (o->f92C != 0) {
        if (insect_InsectPieceIsKing_514b00(o->f92C) != 0) {
            for (i = 0; i < 10; i++) {
                sub = insect_InsectAiGetPiece_5228f0(o, i);
                if (sub != 0 && sub->f71 == o->f930 && insect_InsectPieceIsInPlay_5149e0(sub) != 0) {
                    n++;
                }
            }
            if (n > 2) {
                cfg->f08 |= 2;
            } else {
                cfg->f08 = (cfg->f08 | 0x20) & ~2;
            }
        } else {
            for (i = 0; i < 10; i++) {
                sub = insect_InsectAiGetPiece_5228f0(o, i);
                if (sub != 0 && sub->f71 == o->f930 && insect_InsectPieceIsInPlay_5149e0(sub) != 0) {
                    n++;
                }
            }
            if (n < 4) {
                cfg->f08 |= 0x20;
            }
        }
        insect_InsectAiPushStep_522930(o, 0x1E);
        insect_InsectBoardFindPiece_4ee190(o->f58, o->f92C, &sp1BC, &sp1B8);
        insect_InsectAiActionReset_523410(D_00526030);
        D_00526040[0] = sp1BC;
        D_00526041[0] = sp1B8;
        D_00526044[0] = 1;
        break;
        }
        insect_InsectAiPushStep_522930(o, 0x2E);
        break;

    case 30:
        ent = o->f92C;
        D_004851C0 = 0;
        if (ent == 0) {
            insect_InsectAiPushStep_522930(o, 0x1D);
            break;
        }
        flg = cfg->f08;
        if ((flg & 0x40) == 0) {
            cfg->f08 |= 0x40;
            if ((flg & 0x20) != 0) {
                insect_InsectAiPushStep_522930(o, 0x21);
                break;
            }
        }
        if ((flg & 1) != 0) {
            insect_InsectAiPushStep_522930(o, 0x1F);
            break;
        }
        if ((flg & 2) != 0) {
            insect_InsectAiPushStep_522930(o, 0x20);
            break;
        }
        if ((flg & 4) != 0) {
            if (insect_InsectAiRandChance_522b60(o, cfg->f04) != 0) {
                insect_InsectAiPushStep_522930(o, 0x21);
                break;
            }
        }
        insect_InsectAiPushStep_522930(o, 0x2D);
        break;

    case 45:
        o->f8CC = 0;
        ent = o->f92C;
        if (ent != 0) {
            tgt_case45 = insect_InsectTeamGetPiece_5138d0(o->f54, insect_InsectTeamFindKing_513840(o->f54));
            if (insect_InsectPieceIsKing_514b00(tgt_case45) != 0) {
                insect_InsectBoardPickMoveCell_4edd90(o->f58, ent, tgt_case45, &sp1B4, &sp1B0, 1);
                if (insect_InsectBoardCanMoveAndHit_4ec4a0(o->f58, ent, tgt_case45, sp1B4, sp1B0) != 0) {
                    cmd = insect_InsectAiActionNew_523330(o->fC4);
                    insect_InsectAiActionListAdd_5232e0(o->fC4, cmd);
                    cmd->f00 = ent;
                    cmd->f04 = tgt_case45;
                    cmd->f08 = 0;
                    cmd->f0C = 0;
                    cmd->f14 = 1;
                    cmd->f16 = 0;
                    cmd->f18 = 0;
                    cmd->f1A = 1;
                    cmd->f1B = 1;

                    a = sp1B0;
                    b = sp1B4;
                    cmd->f10 = b;
                    cmd->f11 = a;
                    cmd->f1C++;
                    cmd->f14 = 3;
                    cmd->f08 = tgt_case45;
                    o->f8CC = cmd;
                    insect_InsectAiPushStep_522930(o, 0x2B);
                    break;
                }
            }
            tgt_case45 = insect_InsectBoardFindNearestTarget_4ee000(o->f58, ent, 2);
            insect_InsectBoardPickMoveCell_4edd90(o->f58, ent, tgt_case45, &sp1B4, &sp1B0, 1);
            cmd45_second = insect_InsectAiActionNew_523330(o->fC4);
            if (cmd45_second != 0) {
                insect_InsectAiActionListAdd_5232e0(o->fC4, cmd45_second);
                cmd45_second->f00 = ent;
                cmd45_second->f04 = tgt_case45;
                cmd45_second->f08 = 0;
                cmd45_second->f0C = 0;
                cmd45_second->f14 = 1;
                cmd45_second->f16 = 0;
                cmd45_second->f18 = 0;
                cmd45_second->f1A = 1;
                cmd45_second->f1B = 1;
                a = sp1B0;
                b = sp1B4;
                cmd45_second->f10 = b;
                cmd45_second->f11 = a;
                if (insect_InsectBoardCanMoveAndHit_4ec4a0(o->f58, ent, tgt_case45, sp1B4, sp1B0) != 0) {
                    cmd45_second->f14 = 3;
                    cmd45_second->f08 = tgt_case45;
                } else {
                    if (insect_InsectAiAddAttackActions_521f20(o, ent, sp1B4, sp1B0) != 0) {
                        insect_InsectAiPushStep_522930(o, 0x2A);
                        break;
                    }
                    if (insect_InsectAiRandChance_522b60(o, cfg->f03) != 0) {
                        insect_InsectAiPushStep_522930(o, 0x2B);
                        break;
                    }
                }
                o->f8CC = cmd45_second;
            }
        }
        insect_InsectAiPushStep_522930(o, 0x2E);
        break;

    case 31:
        ent_case31 = o->f92C;
        if (ent_case31 == 0) {
            insect_InsectAiPushStep_522930(o, 0x1D);
            break;
        }
        if (bit == 0) {
            cfg->f08 &= ~1;
            insect_InsectAiPushStep_522930(o, 0x1E);
            break;
        }
        d1 = (f32)cfg->f01 / 100.0f;
        flg = 0;
        if (ent_case31->f38 == 0xB) {
            d0 = D_0047DADC + d1;
            for (i = 0; i < 10; i++) {
                sub = insect_InsectAiGetPiece_5228f0(o, i);
                if (sub != 0 && insect_InsectPieceIsEnemyOf_5149b0(ent_case31, sub) == 0 && ent_case31 != sub &&
                    insect_InsectPieceIsInPlay_5149e0(sub) != 0 && ent_case31->f4F != 0) {
                    if (insect_InsectPieceIsKing_514b00(sub) != 0) {
                        if (insect_InsectPieceGetHpRatio_512e70(sub) <= d0) {
                            best = sub;
                            flg = 1;
                            break;
                        }
                    } else {
                        if (insect_InsectPieceGetHpRatio_512e70(sub) <= d1) {
                            flg = 1;
                            if (best == 0) {
                                best = sub;
                            } else {
                                best = insect_InsectBoardPickNearer_4edf10(o->f58, ent_case31, best, sub);
                            }
                        }
                    }
                }
            }
        } else {
            if (insect_InsectPieceGetHpRatio_512e70(ent_case31) <= d1) {
                for (i = 0; i < 10; i++) {
                    sub = insect_InsectAiGetPiece_5228f0(o, i);
                    if (sub != 0 && insect_InsectPieceIsEnemyOf_5149b0(ent_case31, sub) == 0 &&
                        insect_InsectPieceCanActThunk_514920(sub) != 0 && sub->f38 == 0xB &&
                        sub->f4F != 0) {
                        flg = 1;
                        if (best == 0) {
                            best = sub;
                        } else {
                            best = insect_InsectBoardPickNearer_4edf10(o->f58, ent_case31, best, sub);
                        }
                    }
                }
            }
        }
        if (best == 0) {
            flg = 0;
        }
        if (flg != 0) {
        n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent_case31->f38, ent_case31->f39, ent_case31->f18, o->f94);
        cell = 0;
        insect_InsectBoardPickMoveCell_4edd90(o->f58, ent_case31, best, &sp1AC, &sp1A8, 1);
        cmd = insect_InsectAiActionNew_523330(o->fC4);
        if (cmd != 0) {
            cmd->f00 = ent_case31;
            cmd->f04 = best;
            cmd->f08 = 0;
            cmd->f0C = 0;
            cmd->f14 = 0xD;
            cmd->f16 = 0;
            cmd->f18 = 0;
            cmd->f1A = 1;
            cmd->f1B = 1;
            a = sp1A8;
            b = sp1AC;
            cmd->f10 = b;
            cmd->f11 = a;
            if (ent_case31->f38 == 0xB) {
                if (ent_case31->f4F > 0) {
                    for (i = 0; i < n; i++) {
                        cell = o->f94[i];
                        if (cell != 0 && cell->f62 == 3) {
                            break;
                        }
                    }
                    if (cell != 0) {
                        if (insect_InsectBoardAbilityInRange_4ef5e0(o->f58, ent_case31, best, cell, sp1AC, sp1A8) != 0) {
                            a = sp1A8;
                            b = sp1AC;
                            cmd->f12 = b;
                            cmd->f13 = a;
                            cmd->f0C = cell;
                            cmd->f08 = best;
                        }
                    }
                } else {
                    cfg->f08 &= ~1;
                    insect_InsectAiPushStep_522930(o, 0x1E);
                }
            }
            insect_InsectAiActionListAdd_5232e0(o->fC4, cmd);
            o->f8CC = insect_InsectAiActionListGet_5232c0(o->fC4, 0);
        }
        insect_InsectAiPushStep_522930(o, 0x2E);
        break;
        }
        cfg->f08 &= ~1;
        insect_InsectAiPushStep_522930(o, 0x1E);
        break;

    case 32:
        ent = o->f92C;
        if (ent == 0) {
            insect_InsectAiPushStep_522930(o, 0x1D);
            break;
        }
        n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent->f38, ent->f39, ent->f18, o->f94);
        cnt = ent->f4F;
        tgt_case32 = insect_InsectAiFindKing_522860(o, o->f930);
        cel2 = 0;
        k = cfg->f03;
        if (tgt_case32 == 0) {
            cfg->f08 &= ~2;
            insect_InsectAiPushStep_522930(o, 0x1E);
            break;
        }
        insect_InsectBoardFindPiece_4ee190(o->f58, ent, &sp1A4, &sp1A0);
        spE0 = 1;
        if (insect_InsectPieceIsKing_514b00(ent) != 0) {
            tgt = insect_InsectBoardFindNearestTarget_4ee000(o->f58, tgt_case32, 0);
            if (insect_InsectPieceIsEnemyOf_5149b0(ent, tgt) != 0) {
                if (insect_InsectBoardNearestTargetDist_4ede60(o->f58, tgt_case32, 0) < 4) {
                    spE0 = 0;
                }

                if (bit != 0) {
                    if (cnt > 0) {
                        if (n > 0) {
                            cel2 = o->f94[func_133710() % n];
                            m = insect_InsectAiSpecialCanHit_522310(o, ent, tgt, cel2, &sp1A4, &sp1A0);
                        } else {
                            m = 0;
                        }
                    } else {
                        m = 0;
                    }
                } else {
                    m = 0;
                }
                cmd = insect_InsectAiActionNew_523330(o->fC4);
                if (cmd != 0) {
                    insect_InsectAiActionListAdd_5232e0(o->fC4, cmd);
                    cmd->f00 = ent;
                    cmd->f04 = tgt;
                    cmd->f08 = 0;
                    cmd->f0C = 0;
                    cmd->f14 = 1;
                    cmd->f16 = 0;
                    cmd->f18 = 0;
                    cmd->f1A = 1;
                    cmd->f1B = 1;
                    if (m != 0) {
                        if (cel2 != 0) {
                            best32 = insect_InsectBoardAbilityFindTarget_4ef0f0(o->f58, ent, cel2, sp1A4, sp1A0,
                                                       &sp19C, &sp198, 0);
                            if (best32 != 0) {
                                if (insect_InsectBoardAbilityCanHit_4eea10(o->f58, ent, best32, cel2, &sp1A4,
                                                        &sp1A0, &sp19C, &sp198, 0, 0) != 0) {
                                    a = sp1A0;
                                    b = sp1A4;
                                    cmd->f10 = b;
                                    cmd->f11 = a;
                                    a = sp198;
                                    b = sp19C;
                                    cmd->f12 = b;
                                    cmd->f13 = a;
                                    cmd->f0C = cel2;
                                    cmd->f08 = best32;
                                    cmd->f14 |= 4;
                                }
                            }
                        }
                    } else {
                        ok = 0;
                        for (i = 0; i < 10; i++) {
                            best32 = insect_InsectAiGetPiece_5228f0(o, i);
                            if (best32 != 0 && best32->f71 == o->f930 &&
                                insect_InsectPieceIsInPlay_5149e0(best32) != 0 && best32 != ent) {
                                ok = 1;
                            }
                        }
                        if (ok != 0) {
                            insect_InsectBoardPickMoveCell_4edd90(o->f58, ent, tgt, &sp1A4, &sp1A0, 0);
                        } else {
                            insect_InsectBoardPickMoveCell_4edd90(o->f58, ent,
                                                insect_InsectAiFindKing_522860(o, insect_InsectAiGetEnemySide_521f10(o)),
                                                &sp1A4, &sp1A0, 1);
                            insect_InsectAiPushStep_522930(o, 0x2D);
                            break;
                        }
                    }
                    a = sp1A0;
                    b = sp1A4;
                    cmd->f10 = b;
                    cmd->f11 = a;
                    if (insect_InsectBoardCanMoveAndHit_4ec4a0(o->f58, ent, tgt, sp1A4, sp1A0) != 0) {
                        if ((s32)(cfg->f08 & 0x4000) != 0) {
                            if (insect_InsectBattleSimExchangeMaybe_50f150(ent, tgt, 0) != 0) {
                                cmd->f08 = tgt;
                                cmd->f14 &= ~2u;
                            }
                        } else {
                            cmd->f08 = tgt;
                            cmd->f14 |= 2;
                        }
                    }
                    o->f8CC = insect_InsectAiActionListGet_5232c0(o->fC4, 0);
                }
            }
            if (spE0 != 0) {
                insect_InsectAiPickCoverCellMaybe_5224c0(o, ent, &sp1A4, &sp1A0);
                cm2 = insect_InsectAiActionNew_523330(o->fC4);
                if (cm2 != 0) {
                    insect_InsectAiActionListAdd_5232e0(o->fC4, cm2);
                    cm2->f00 = ent;
                    cm2->f04 = 0;
                    a = sp1A0;
                    b = sp1A4;
                    cm2->f10 = b;
                    cm2->f11 = a;
                    cm2->f14 = 1;
                    o->f8CC = cm2;
                }
            }
            insect_InsectAiPushStep_522930(o, 0x2E);
            break;
        }
        spDC = 0;
        tgt = insect_InsectBoardFindNearestTarget_4ee000(o->f58, tgt_case32, 0);
        if (insect_InsectPieceIsEnemyOf_5149b0(tgt_case32, tgt) != 0) {
        insect_InsectBoardPickMoveCell_4edd90(o->f58, ent, tgt, &sp1A4, &sp1A0, 1);
        if (bit != 0 && cnt > 0 && n > 0) {
            cel2 = o->f94[func_133710() % n];
            spDC = insect_InsectAiSpecialCanHit_522310(o, ent, tgt, cel2, &sp1A4, &sp1A0);
        }
        cmd = insect_InsectAiActionNew_523330(o->fC4);
        if (cmd != 0) {
            insect_InsectAiActionListAdd_5232e0(o->fC4, cmd);
            cmd->f00 = ent;
            cmd->f04 = tgt;
            cmd->f14 = 1;
            a = sp1A0;
            b = sp1A4;
            cmd->f10 = b;
            cmd->f11 = a;
            if (insect_InsectBoardCanMoveAndHit_4ec4a0(o->f58, ent, tgt, sp1A4, sp1A0) != 0) {
            ok = 0;
            if (spDC != 0) {
                if (insect_InsectAiRandChance_522b60(o, k) != 0) {
                    best32 = insect_InsectBoardAbilityFindTarget_4ef0f0(o->f58, ent, cel2, sp1A4, sp1A0,
                                               &sp194, &sp190, 0);
                    if (best32 != 0) {
                        if (insect_InsectBoardAbilityCanHit_4eea10(o->f58, ent, best32, cel2, &sp1A4, &sp1A0,
                                                &sp194, &sp190, 0, 0) != 0) {
                            a = sp1A0;
                            b = sp1A4;
                            cmd->f10 = b;
                            cmd->f11 = a;
                            a = sp190;
                            b = sp194;
                            cmd->f12 = b;
                            cmd->f13 = a;
                            cmd->f0C = cel2;
                            cmd->f08 = best32;
                            cmd->f14 |= 5;
                        }
                    }
                    ok = 1;
                }
            }
            if (ok == 0) {
                cfg->f08 &= ~2;
                insect_InsectAiPushStep_522930(o, 0x2D);
                break;
            }
            } else {
                cfg->f08 &= ~2;
                insect_InsectAiPushStep_522930(o, 0x2D);
                break;
            }
        }
        o->f8CC = insect_InsectAiActionListGet_5232c0(o->fC4, 0);
        insect_InsectAiPushStep_522930(o, 0x2E);
        break;
        }
        cfg->f08 &= ~2;
        insect_InsectAiPushStep_522930(o, 0x1E);
        break;

    case 33:
        ent = o->f92C;
        if (ent == 0) {
            insect_InsectAiPushStep_522930(o, 0x1D);
            break;
        }
        tgt_case33 = insect_InsectAiFindKing_522860(o, insect_InsectAiGetEnemySide_521f10(o));
        if (tgt_case33 == 0) {
            cfg->f08 &= ~4;
            insect_InsectAiPushStep_522930(o, 0x1E);
            break;
        }
        insect_InsectBoardPickMoveCell_4edd90(o->f58, ent, tgt_case33, &sp18C, &sp188, 1);
        cmd = insect_InsectAiActionNew_523330(o->fC4);
        if (cmd != 0) {
            insect_InsectAiActionListAdd_5232e0(o->fC4, cmd);
            cmd->f00 = ent;
            a = sp188;
            b = sp18C;
            cmd->f10 = b;
            cmd->f11 = a;
            cmd->f14 = 1;
        }
        if (insect_InsectBoardCanMoveAndHit_4ec4a0(o->f58, ent, tgt_case33, sp18C, sp188) != 0) {
            cmd->f14 |= 2;
            cmd->f04 = tgt_case33;
            cmd->f08 = tgt_case33;
            o->f8CC = insect_InsectAiActionListGet_5232c0(o->fC4, 0);
            n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent->f38, ent->f39, ent->f18, o->f94);
            if (n > 0) {
                i = 0;
                if (n != 0) {
                    i = func_133710() % n;
                }
                cell_case33 = o->f94[i];
                best = insect_InsectBoardAbilityFindTarget_4ef0f0(o->f58, ent, cell_case33, sp18C, sp188,
                                           &sp184, &sp180, 0);
                if (best != 0) {
                    if (insect_InsectBoardAbilityCanHit_4eea10(o->f58, ent, best, cell_case33, &sp18C, &sp188,
                                            &sp184, &sp180, 0, 0) != 0) {
                        a = sp188;
                        b = sp18C;
                        cmd->f10 = b;
                        cmd->f11 = a;
                        a = sp180;
                        b = sp184;
                        cmd->f12 = b;
                        cmd->f13 = a;
                        cmd->f0C = cell_case33;
                        cmd->f08 = best;
                        cmd->f14 |= 4;
                    }
                }
            }
            insect_InsectAiPushStep_522930(o, 0x2E);

            goto c33_tail;
        }
        if ((s32)(cfg->f08 & 0x20) != 0) {
            cmd->f14 = 7;
            cmd->f04 = tgt_case33;
            cmd->f08 = 0;
            for (i = 0; i < 10; i++) {
                tgt_case33 = insect_InsectAiGetPiece_5228f0(o, i);
                if (tgt_case33 != 0) {
                    if (insect_InsectBoardCanMoveAndHit_4ec4a0(o->f58, ent, tgt_case33, sp18C, sp188) != 0) {
                        cmd->f08 = tgt_case33;
                        cmd->f04 = tgt_case33;
                        o->f8CC = insect_InsectAiActionListGet_5232c0(o->fC4, 0);
                        insect_InsectAiPushStep_522930(o, 0x2E);
                        return;
                    }
                }
            }
            o->f8CC = insect_InsectAiActionListGet_5232c0(o->fC4, 0);
            insect_InsectAiPushStep_522930(o, 0x2E);
            break;
        }
        if (insect_InsectAiAddAttackActions_521f20(o, ent, sp18C, sp188) != 0) {
            insect_InsectAiPushStep_522930(o, 0x2A);
        } else {
            cfg->f08 &= ~4;
            insect_InsectAiPushStep_522930(o, 0x1E);
        }
        return;
    c33_tail:
        insect_InsectAiPushStep_522930(o, 0x2E);
        return;

    case 42:
        if (insect_InsectAiRandChance_522b60(o, cfg->f03) != 0) {
            insect_InsectAiPushStep_522930(o, 0x2B);
        } else {
            insect_InsectAiPushStep_522930(o, 0x2C);
        }
        break;

    case 43:
        n = insect_InsectAiActionListCount_5232d0(o->fC4);
        for (i_case43 = 0; i_case43 < n; i_case43++) {
            cmd = insect_InsectAiActionListGet_5232c0(o->fC4, i_case43);
            if (cmd == 0) {
                continue;
            }
            if (cmd->f0C == 0) {
                tgt_case43 = cmd->f08;
                ent = cmd->f00;
                if (tgt_case43 == 0) {
                    tgt_case43 = cmd->f04;
                }
                if (ent->f4F > 0) {
                    sp17C = cmd->f10;
                    sp178 = cmd->f11;
                    m = insect_InsectAbilityTableFilter_51d020(o->f5C, ent->f38, ent->f39, ent->f18, o->f94);
                    j = 0;
                    if (m != 0) {
                        j = func_133710() % m;
                    }
                    cell = o->f94[j];
                    if (cell != 0) {
                        if (insect_InsectBoardAbilityCanHit_4eea10(o->f58, ent, tgt_case43, cell, &sp17C, &sp178,
                                                &sp174, &sp170, 0, 0) != 0) {
                            a = sp178;
                            b = sp17C;
                            cmd->f10 = b;
                            cmd->f11 = a;
                            cmd->f0C = cell;
                            a = sp170;
                            b = sp174;
                            cmd->f12 = b;
                            cmd->f13 = a;
                            cmd->f14 |= 4;
                        }
                    }
                }
            }
        }
        insect_InsectAiPushStep_522930(o, 0x2C);
        break;

    case 44:
        n = insect_InsectAiActionListCount_5232d0(o->fC4);
        ent = o->f92C;
        o->f8CC = 0;
        o->f8CC = insect_InsectAiActionListGet_5232c0(o->fC4, 0);
        for (i = 0; i < n; i++) {
            cmd = insect_InsectAiActionListGet_5232c0(o->fC4, i);
            if (cmd == 0) {
                continue;
            }
            ok = 0;
            if (o->f8CC != 0) {
                tgt = cmd->f08;
                sub = o->f8CC->f08;
                if (tgt != 0 && sub != 0) {
                    switch (cfg->f02) {
                    case 0:
                        if (tgt->f18 > sub->f18) {
                            ok = 1;
                        }
                        break;
                    case 1:
                        if (tgt->f18 < sub->f18) {
                            ok = 1;
                        }
                        break;
                    case 2:
                        if (tgt->f1A > sub->f1A) {
                            ok = 1;
                        }
                        break;
                    case 3:
                        if (tgt->f1A < sub->f1A) {
                            ok = 1;
                        }
                        break;
                    case 4:
                        if (tgt->f26 < sub->f26) {
                            ok = 1;
                        }
                        break;
                    case 5:
                        if (tgt->f28 < sub->f28) {
                            ok = 1;
                        }
                        break;
                    case 6:
                        insect_InsectBoardPickNearer_4edf10(o->f58, ent, tgt, sub);
                        ok = 1;
                        break;
                    }
                } else {
                    if (tgt != 0) {
                        ok = 1;
                    }
                }
            } else {
                ok = 1;
            }
            if (ok != 0) {
                if (o->f8CC->f1C <= cmd->f1C) {
                    o->f8CC = cmd;
                }
            }
        }
        insect_InsectAiPushStep_522930(o, 0x2E);
        break;

    case 35:
        insect_InsectAiPlanScissorThrow_51f1d0(o, 0);
        insect_InsectAiPushStep_522930(o, 0x2E);
        break;

    case 41:
        if (o->f8CC != 0) {
            ent_case41 = o->f8CC->f00;
            if (ent_case41 != 0) {
                cell = 0;
                insect_InsectPieceClearStatus_513340(ent_case41, 0x12);
                n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent_case41->f38, ent_case41->f39, ent_case41->f18, o->f94);
                if (n > 0 && ent_case41->f4F > 0) {
                    i = 0;
                    if (n != 0) {
                        i = func_133710() % n;
                    }
                    cell = o->f94[i];
                }
                cnt = 0;
                for (i = 0; i < 10; i++) {
                    sub = insect_InsectAiGetPiece_5228f0(o, i);
                    if (sub != 0) {
                        insect_InsectPieceClearStatus_513340(sub, 0x12);
                        if (insect_InsectPieceIsEnemyOf_5149b0(ent_case41, sub) == 0 &&
                            insect_InsectPieceIsInPlay_5149e0(sub) != 0) {
                            cnt++;
                        }
                    }
                }
                insect_InsectBoardFindPiece_4ee190(o->f58, ent_case41, &sp16C, &sp168);
                insect_InsectBoardCalcMoveRange_4ed180(o->f58, ent_case41);
                best = 0;
                for (a = 0; a < 7; a++) {
                    for (b = 0; b < 5; b++) {
                        if (insect_InsectBoardIsMovable_4ee930(o->f58, b, a) != 0) {
                            sub = 0;
                            if (cnt < 5) {
                                if (D_004851BC != 0) {
                                    sub = insect_InsectAiSpecialTargetBerserker_51ed80(o, ent_case41, cell, b, a, 0, best);
                                } else {
                                    insect_InsectAiSpecialTargetBerserker_51ed80(o, ent_case41, cell, b, a, 1, 0);
                                    best = ent_case41;
                                    if (insect_InsectPieceTestStatus_513280(ent_case41, 0x12) != 0) {
                                        sp16C = b;
                                        sp168 = a;
                                    }
                                }
                            } else {
                                sub = insect_InsectAiSpecialTargetBerserker_51ed80(o, ent_case41, cell, b, a, 0, best);
                            }
                            if (sub != 0) {
                                best = sub;
                                sp16C = b;
                                sp168 = a;
                            }
                        }
                    }
                }
                if (best != 0) {
                    flg = 0;
                    if (cnt < 5) {
                        if (insect_InsectPieceTestStatus_513280(best, 0x12) != 0) {
                            flg = 1;
                        } else if (D_004851BC == 0) {
                            D_004851BC = 1;
                            break;
                        }
                    }
                    insect_InsectBoardFindPiece_4ee190(o->f58, best, &sp164, &sp160);

                    cel2_case41 = 0;
                    kind = 3;
                    a = sp168;
                    cm2 = o->f8CC;
                    b = sp16C;
                    cm2->f10 = b;
                    cm2->f11 = a;
                    o->f8CC->f08 = best;
                    o->f8CC->f04 = best;
                    a = sp168;
                    cm2 = o->f8CC;
                    b = sp16C;
                    cm2->f12 = b;
                    cm2->f13 = a;
                    if (flg != 0) {
                        cel2_case41 = cell;
                        kind = 5;
                    }
                    o->f8CC->f0C = cel2_case41;
                    o->f8CC->f14 = kind;
                }
            }
        }
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x2F);
        break;

    case 40:
        if (o->f8CC != 0) {
            ent_case40 = o->f8CC->f00;

            cell = 0;
            if (ent_case40 != 0) {
                n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent_case40->f38, ent_case40->f39, ent_case40->f18, o->f94);
                if (n > 0 && ent_case40->f4F > 0) {
                    i = 0;
                    if (n != 0) {
                        i = func_133710() % n;
                    }
                    cell = o->f94[i];
                }
                cnt = 0;
                for (i = 0; i < 10; i++) {
                    sub = insect_InsectAiGetPiece_5228f0(o, i);
                    if (sub != 0) {
                        insect_InsectPieceClearStatus_513340(sub, 0x12);
                        if (insect_InsectPieceIsEnemyOf_5149b0(ent_case40, sub) == 0 &&
                            insect_InsectPieceIsInPlay_5149e0(sub) != 0) {
                            cnt++;
                        }
                    }
                }
                insect_InsectBoardFindPiece_4ee190(o->f58, ent_case40, &sp15C, &sp158);
                insect_InsectBoardCalcMoveRange_4ed180(o->f58, ent_case40);
                best = 0;
                for (a = 0; a < 7; a++) {
                    for (b = 0; b < 5; b++) {
                        if (insect_InsectBoardIsMovable_4ee930(o->f58, b, a) != 0) {
                            sub = 0;
                            if (cnt < 4) {
                                if (D_004851BC != 0) {
                                    sub = insect_InsectAiSpecialTargetEmperorsRage_51e8f0(o, ent_case40, cell, b, a, 1, best);
                                } else {
                                    sub = insect_InsectAiSpecialTargetEmperorsRage_51e8f0(o, ent_case40, cell, b, a, 0, best);
                                }
                            } else {
                                if (cell != 0) {
                                    sub = insect_InsectAiSpecialTargetEmperorsRage_51e8f0(o, ent_case40, cell, b, a, 1, best);
                                }
                            }
                            if (sub != 0) {
                                best = sub;
                                sp15C = b;
                                sp158 = a;
                            }
                        }
                    }
                }
                if (best != 0) {
                    if (cnt < 4 && D_004851BC == 0) {
                        insect_InsectBoardFindPiece_4ee190(o->f58, best, &sp154, &sp150);
                        a = sp158;
                        cm2 = o->f8CC;
                        b = sp15C;
                        cm2->f10 = b;
                        cm2->f11 = a;
                        o->f8CC->f08 = best;
                        o->f8CC->f04 = best;
                        o->f8CC->f0C = 0;
                        a = sp150;
                        cm2 = o->f8CC;
                        b = sp154;
                        cm2->f12 = b;
                        cm2->f13 = a;
                        o->f8CC->f14 = 3;
                    } else {
                        insect_InsectBoardFindPiece_4ee190(o->f58, best, &sp14C, &sp148);
                        a = sp158;
                        cm2 = o->f8CC;
                        b = sp15C;
                        cm2->f10 = b;
                        cm2->f11 = a;
                        o->f8CC->f08 = best;
                        o->f8CC->f0C = cell;
                        a = sp148;
                        cm2 = o->f8CC;
                        b = sp14C;
                        cm2->f12 = b;
                        cm2->f13 = a;
                        o->f8CC->f14 = 5;
                    }
                } else {
                    if (cnt < 4 && D_004851BC == 0) {
                        D_004851BC = 1;
                        break;
                    }
                }
            }
        }
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x2F);
        break;

    case 39:
        flg_case39 = 0;
        m = insect_InsectAiRandChance_522b60(o, 0x32);
        switch (func_3CCAC0(*(void **)((u8 *)func_1FEDE0() + 0x10), 6)) {
        case 0:
            break;
        case 1:
        case 2:
            if (insect_InsectAiRandChance_522b60(o, 0x14) != 0) {
                flg_case39 = 1;
            }
            break;
        case 3:
        case 4:
            if (insect_InsectAiRandChance_522b60(o, 0x32) != 0) {
                flg_case39 = 1;
            }
            break;
        case 5:
        case 6:
            flg_case39 = 1;
            break;
        }
        if (o->f8CC != 0 && m != 0) {
            ent_case39 = o->f8CC->f00;
            if (ent_case39 != 0) {
                n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent_case39->f38, ent_case39->f39, ent_case39->f18, o->f94);
                if (n > 0 && ent_case39->f4F > 0) {
                    i = 0;
                    if (n != 0) {
                        i = func_133710() % n;
                    }
                    cell = o->f94[i];
                    if (cell != 0) {
                        insect_InsectBoardFindPiece_4ee190(o->f58, ent_case39, &sp144, &sp140);
                        insect_InsectBoardCalcMoveRange_4ed180(o->f58, ent_case39);
                        best = 0;
                        for (a = 6; a >= 0; a--) {
                            for (b = 0; b < 5; b++) {
                                if (insect_InsectBoardIsMovable_4ee930(o->f58, b, a) != 0) {
                                    sub = insect_InsectAiSpecialTargetCharmBeam_51e560(o, ent_case39, cell, b, a, flg_case39, best);
                                    if (sub != 0) {
                                        best = sub;
                                        sp144 = b;
                                        sp140 = a;
                                    }
                                }
                            }
                        }
                        if (best != 0) {
                            insect_InsectBoardFindPiece_4ee190(o->f58, best, &sp13C, &sp138);
                            a = sp140;
                            cm2 = o->f8CC;
                            b = sp144;
                            cm2->f10 = b;
                            cm2->f11 = a;
                            o->f8CC->f08 = best;
                            o->f8CC->f0C = cell;
                            a = sp138;
                            cm2 = o->f8CC;
                            b = sp13C;
                            cm2->f12 = b;
                            cm2->f13 = a;
                            o->f8CC->f14 = 5;
                        }
                    }
                }
            }
        }
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x2F);
        break;

    case 38:
        if (o->f8CC != 0) {
            ent_case38 = o->f8CC->f00;
            if (ent_case38 != 0) {
                if (insect_InsectPieceIsKing_514b00(ent_case38) != 0) {
                    if (insect_InsectPieceGetHpRatio_512e70(ent_case38) <= 8.0f) {
                        insect_InsectAiPushState_5229e0(o, 4);
                        insect_InsectAiPushStep_522930(o, 0x2F);
                    }
                }
                n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent_case38->f38, ent_case38->f39, ent_case38->f18, o->f94);
                if (n > 0 && ent_case38->f4F > 0) {
                    i = 0;
                    if (n != 0) {
                        i = func_133710() % n;
                    }
                    cell = o->f94[i];
                    if (cell != 0) {
                        insect_InsectBoardFindPiece_4ee190(o->f58, ent_case38, &sp134, &sp130);
                        insect_InsectBoardCalcMoveRange_4ed180(o->f58, ent_case38);
                        best = 0;
                        for (a = 6; a >= 0; a--) {
                            for (b = 0; b < 5; b++) {
                                if (insect_InsectBoardIsMovable_4ee930(o->f58, b, a) != 0) {
                                    sub = insect_InsectAiSpecialTargetCannonBlast_51e3c0(o, ent_case38, cell, b, a);
                                    if (sub != 0) {
                                        ok = 0;
                                        if (best != 0) {
                                            if (insect_InsectPieceIsKing_514b00(best) != 0) {
                                                if (insect_InsectPieceGetHpRatio_512e70(sub) <= D_0047D344) {
                                                    ok = 1;
                                                }
                                            } else {
                                                if (insect_InsectPieceGetHpRatio_512e70(sub) > D_0047D344) {
                                                    d0 = insect_InsectPieceGetHpRatio_512e70(sub);
                                                    if (d0 >= insect_InsectPieceGetHpRatio_512e70(best)) {
                                                        ok = 1;
                                                    }
                                                }
                                            }
                                        } else {
                                            ok = 1;
                                        }
                                        if (ok != 0) {
                                            best = sub;
                                            sp134 = b;
                                            sp130 = a;
                                        }
                                    }
                                }
                            }
                        }
                        if (best != 0 && ent_case38->f4F > 0) {
                            insect_InsectBoardFindPiece_4ee190(o->f58, best, &sp12C, &sp128);
                            a = sp130;
                            cm2 = o->f8CC;
                            b = sp134;
                            cm2->f10 = b;
                            cm2->f11 = a;
                            o->f8CC->f08 = best;
                            o->f8CC->f0C = cell;
                            a = sp128;
                            cm2 = o->f8CC;
                            b = sp12C;
                            cm2->f12 = b;
                            cm2->f13 = a;
                            o->f8CC->f14 = 5;
                        }
                    }
                }
            }
        }
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x2F);
        break;

    case 37:
        if (o->f8CC != 0) {
            ent_case37 = o->f8CC->f00;
            if (ent_case37 != 0) {
                n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent_case37->f38, ent_case37->f39, ent_case37->f18, o->f94);
                if (n > 0 && ent_case37->f4F > 0) {
                    i = 0;
                    if (n != 0) {
                        i = func_133710() % n;
                    }
                    cell_case37 = o->f94[i];
                    if (cell_case37 != 0) {
                        insect_InsectBoardFindPiece_4ee190(o->f58, ent_case37, &sp124, &sp120);
                        insect_InsectBoardCalcMoveRange_4ed180(o->f58, ent_case37);
                        best = 0;
                        for (a = 0; a < 7; a++) {
                            for (b = 0; b < 5; b++) {
                                if (insect_InsectBoardIsMovable_4ee930(o->f58, b, a) != 0) {
                                    sub_case37 = insect_InsectAiSpecialTargetScissorThrow_51e150(o, ent_case37, cell_case37, b, a);
                                    if (sub_case37 != 0) {
                                        if (best == 0) {
                                            best = sub_case37;
                                            sp124 = b;
                                            sp120 = a;
                                        } else if (insect_InsectPieceIsKing_514b00(best) == 0) {
                                            best = sub_case37;
                                            sp124 = b;
                                            sp120 = a;
                                        }
                                    }
                                }
                            }
                        }
                        if (best != 0 && ent_case37->f4F > 0) {
                            insect_InsectBoardFindPiece_4ee190(o->f58, best, &sp11C, &sp118);
                            a = sp120;
                            cm2 = o->f8CC;
                            b = sp124;
                            cm2->f10 = b;
                            cm2->f11 = a;
                            o->f8CC->f08 = best;
                            o->f8CC->f0C = cell_case37;
                            a = sp118;
                            cm2 = o->f8CC;
                            b = sp11C;
                            cm2->f12 = b;
                            cm2->f13 = a;
                            o->f8CC->f14 = 5;
                        }
                    }
                }
            }
        }
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x2F);
        break;

    case 36:
        if (o->f8CC != 0) {
            ent_case36 = o->f8CC->f00;
            if (ent_case36 != 0) {
                n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent_case36->f38, ent_case36->f39, ent_case36->f18, o->f94);
                if (n > 0 && ent_case36->f4F > 0) {
                    i = 0;
                    if (n != 0) {
                        i = func_133710() % n;
                    }
                    cell_case36 = o->f94[i];
                    insect_InsectBoardFindPiece_4ee190(o->f58, ent_case36, &sp114, &sp110);
                    ok = 0;
                    for (i = 0; i < 10; i++) {
                        insect_InsectBoardCalcMoveRange_4ed180(o->f58, ent_case36);
                        sub = insect_InsectAiGetPiece_5228f0(o, i);
                        if (sub == 0) {
                            continue;
                        }
                        if (insect_InsectPieceIsEnemyOf_5149b0(ent_case36, sub) != 0 &&
                            insect_InsectPieceIsInPlay_5149e0(sub) != 0) {
                            insect_InsectBoardFindPiece_4ee190(o->f58, sub, &sp10C, &sp108);
                            k = 1;
                            if (ent_case36->f71 == 0) {
                                k = -1;
                            }
                            sp108 = sp108 - k;
                            sp104 = sp10C;
                            sp100 = sp108;
                            if (insect_InsectBoardAbilityCanHit_4eea10(o->f58, ent_case36, sub, cell_case36, &sp10C, &sp108,
                                                    &sp104, &sp100, 0, 0) != 0) {
                                flg = 0;
                                if (insect_InsectPieceIsKing_514b00(sub) != 0) {
                                    flg = 1;
                                } else if (ok == 0) {
                                    flg = 1;
                                }
                                if (flg != 0 && ent_case36->f4F > 0) {
                                    ok = 1;
                                    o->f8CC->f0C = cell_case36;
                                    o->f8CC->f04 = sub;
                                    o->f8CC->f08 = sub;
                                    a = sp108;
                                    cm2 = o->f8CC;
                                    b = sp10C;
                                    cm2->f10 = b;
                                    cm2->f11 = a;
                                    a = sp100;
                                    cm2 = o->f8CC;
                                    b = sp104;
                                    cm2->f12 = b;
                                    cm2->f13 = a;
                                    o->f8CC->f14 = 5;
                                }
                            }
                        }
                    }
                }
            }
        }
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x2F);
        break;

    case 25:
        insect_InsectAiPushState_5229e0(o, 3);
        insect_InsectAiPushStep_522930(o, 1);
        break;

    case 46:
        if (o->f8CC != 0) {

            cmd = o->f8CC;
            ent = cmd->f00;
            tgt_case46 = cmd->f08;
            spFC = cmd->f10;
            spF8 = cmd->f11;
            o->f8CC->f14 |= 1;
            if (tgt_case46 != 0 && ent != 0) {
                o->f48 = ent;
                o->f4C = tgt_case46;
                n = insect_InsectAbilityTableFilter_51d020(o->f5C, ent->f38, ent->f39, ent->f18, o->f94);
                if (n > 0 && ent->f4F > 0 && o->f8CC->f0C == 0) {
                    i = 0;
                    if (n != 0) {
                        i = func_133710() % n;
                    }
                    cell_case46 = o->f94[i];
                    if (cell_case46 != 0 && (s32)(cfg->f08 & 0x8000) != 0 &&
                        insect_InsectAiRandChance_522b60(o, cfg->f03) != 0 && ent != 0) {
                        best = insect_InsectBoardAbilityFindTarget_4ef0f0(o->f58, ent, cell_case46, spFC, spF8,
                                                   &spF4, &spF0, tgt_case46);
                        if (best != 0) {
                            if (insect_InsectBoardAbilityCanHit_4eea10(o->f58, ent, best, cell_case46, &spFC, &spF8,
                                                    &spF4, &spF0, 0, 0) != 0) {
                                a = spF8;
                                cm2 = o->f8CC;
                                b = spFC;
                                cm2->f10 = b;
                                cm2->f11 = a;
                                a = spF0;
                                cm2 = o->f8CC;
                                b = spF4;
                                cm2->f12 = b;
                                cm2->f13 = a;
                                o->f8CC->f0C = cell_case46;
                                o->f8CC->f14 |= 4;
                                if (best != tgt_case46) {
                                    o->f8CC->f08 = best;
                                    o->f8CC->f14 &= ~2u;
                                }
                            }
                        }
                    }
                }
            }
            flg = 0;
            switch (func_3CCAC0(*(void **)((u8 *)func_1FEDE0() + 0x10), 6)) {
            case 0:
                break;
            case 1:
            case 2:
                if (insect_InsectAiRandChance_522b60(o, 0x28) != 0) {
                    flg = 1;
                }
                break;
            case 3:
            case 4:
                if (insect_InsectAiRandChance_522b60(o, 0x50) != 0) {
                    flg = 1;
                }
                break;
            case 5:
            case 6:
                flg = 1;
                break;
            }
            if (arg1 != 0) {
                flg = 1;
            }
            if (ent != 0 && flg != 0) {
                switch (ent->f38) {
                case 8:
                    if (insect_InsectPieceIsKing_514b00(ent) == 0) {
                        insect_InsectAiPushStep_522930(o, 0x24);
                        return;
                    }
                    break;
                case 4:
                    insect_InsectAiPushStep_522930(o, 0x25);
                    return;
                case 2:
                    insect_InsectAiPushStep_522930(o, 0x26);
                    return;
                case 0xE:
                    insect_InsectAiPushStep_522930(o, 0x27);
                    return;
                case 0xF:
                    insect_InsectAiPushStep_522930(o, 0x28);
                    return;
                case 0x10:
                    insect_InsectAiPushStep_522930(o, 0x29);
                    return;
                }
            }
        }
        insect_InsectAiPushState_5229e0(o, 4);
        insect_InsectAiPushStep_522930(o, 0x2F);
        break;

    case 34:
    case 47:
        break;
    }
}
