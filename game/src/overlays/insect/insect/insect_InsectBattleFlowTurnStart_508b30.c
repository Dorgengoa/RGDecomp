/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowTurnStart_508b30 1
#include "port/game_protos.h"
#line 1
/* insect 0x00508B30 -- 1,556 B / 389 words.  MATCHES (ix81).
 *
 * This closed the ix36 FAMILY WORD, open since session 36 and shared with
 * insect_InsectBattleMenuResultBanner_4fc780 and insect_InsectBattleFlowMatchStart_505530.  Retail rematerialises the
 * frame address of the 16-byte fill buffer AFTER the call, in a CALLER-SAVED
 * register:
 *
 *     addiu $a0,$sp,176        <- the call argument
 *     jal   004F0220
 *     move  $a1,$s5
 *     addiu $v0,$sp,176        <- a SECOND, caller-saved materialisation
 *     lwc1  $f0,0($v0) ...     <- the copy runs off it
 *
 * mwcc folds a frame-constant address into $sp displacements UNCONDITIONALLY
 * (levers.d/mwcc-copy-base-addressing-map, ~190 probe arms over ix59/ix70/ix80
 * plus a corpus-wide screen this session that found the shape in NONE of the
 * 14,076 matched units).  The ix59 one-sided-if phi defeats the fold but by
 * construction gives the pointer two reaching defs STRADDLING the call, so it
 * can only ever be callee-saved -- that was this unit's 17 bad.
 *
 * The lever is a UNION PUN: write the address through the union's INTEGER
 * member and read it back through its POINTER member.  mwcc's propagator is
 * member-typed, so it cannot forward the address across the pun; the value
 * stays opaque, is materialised at the USE (after the call) and therefore
 * lands in a caller-saved register.  A plain integer round-trip
 * (`*(F220Quad *)(s32)&q`) does NOT work -- it makes the copy real but still
 * folded.  See levers.d/mwcc-union-address-pun.
 *
 * The union must be declared where it does not grow the frame: it is an
 * aggregate, so mwcc reserves a slot for it above the existing ones even
 * though the value never reaches memory.  This frame has the slack; the two
 * sibling units do not (see their headers).
 *
 * ix59 broke this unit's LENGTH barrier and left 17; ix81 closes them.
 */
#include "types.h"

typedef struct F220Quad {
    s32 a;                          /* +0x00 */
    s32 b;                          /* +0x04 */
    s32 c;                          /* +0x08 */
    f32 d;                          /* +0x0C */
} F220Quad;

typedef struct Quad16 { s32 w0; s32 w1; s32 w2; s32 w3; } Quad16;
typedef union QPun { F220Quad *p; s32 i; } QPun;

typedef struct Ent {
    u8  pad000[0x38];
    s8  f38;                        /* +0x38 */
    s8  f39;                        /* +0x39 */
    u8  pad3A[0x3D - 0x3A];
    s8  f3D;                        /* +0x3D */
    u8  pad3E[0x3F - 0x3E];
    s8  f3F;                        /* +0x3F */
    s8  f40;                        /* +0x40 */
    s8  f41;                        /* +0x41 */
    s8  f42;                        /* +0x42 */
    u8  pad43[0x4C - 0x43];
    s8  f4C;                        /* +0x4C */
    u8  pad4D[0x4F - 0x4D];
    s8  f4F;                        /* +0x4F */
    u8  pad50[0x5C - 0x50];
    s32 f5C;                        /* +0x5C */
    u8  pad60[0x71 - 0x60];
    s8  f71;                        /* +0x71 */
} Ent;

typedef struct Ins {
    u8    pad0000[0x4960];
    u8    f4960[0x4A9B - 0x4960];   /* +0x4960 */
    u8    f4A9B[13][5];             /* +0x4A9B */
    u8    pad4ADC[0x4B04 - 0x4ADC];
    u8    f4B04[13][5];             /* +0x4B04 */
    u8    pad4B45[0x5B08 - 0x4B45];
    s32 (*f5B08)[12];               /* +0x5B08 */
    u8    pad5B0C[0x5B14 - 0x5B0C];
    s32   f5B14;                    /* +0x5B14 */
    u8    pad5B18[0x5DA8 - 0x5B18];
    s32   f5DA8;                    /* +0x5DA8 */
    u8    pad5DAC[0x5EF1 - 0x5DAC];
    u8    f5EF1;                    /* +0x5EF1 */
} Ins;

extern u8 insect_D_00524EC0[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void  Sprintf_1343b8(char *t, s32 a, s32 b);
/*rgp*/

void insect_InsectBattleFlowTurnStart_508b30(Ins *o)
{
    Quad16   q __attribute__((aligned(16)));
    F220Quad w __attribute__((aligned(16)));
    u8   *p20;
    u8   *sl;
    s32   i;
    u8   *p22;
    s32   j;
    s32   x;
    s32   y;
    Ent  *p;
    char *buf;
    s32   n;
    s32   m;
    s32   k;
    s32   f;

    p20 = (u8 *)o + 0x506C;
    p22 = (u8 *)o + 0x5080;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleClearFlag_50da90(o, 0x34);
        insect_InsectBattleSwapSide_50e1a0(o);
        insect_InsectBattleCursorNextPiece_4f0bd0(o, 2, 1, 0, -1, 0);
        insect_InsectBattleClearFlag_50da90(o, 0x15);
        insect_InsectBattleClearFlag_50da90(o, 0x27);
        insect_InsectBattleClearFlag_50da90(o, 0x28);
        if (insect_InsectBattleTestFlag_50da40(o, o->f5EF1) == 0) {
            insect_InsectBattleSetFlag_50dad0(o, 0x15);
            insect_InsectBattleSetFlag_50dad0(o, 0x27);
        }
        f = o->f5EF1;
        for (i = 0; i < 2; i++) {
            sl = (u8 *)o + i * 0x994 + 0x35F8;
            for (j = 0; j < 5; j++) {
                p = ((Ent *)insect_InsectTeamGetPiece_5138d0(sl, j));
                if (insect_InsectPieceIsInPlay_5149e0(p) != 0 && f == p->f71) {
                    buf = (char *)o + 0x5F82;
                    if (p->f38 == 0xC) {
                        if (insect_InsectPieceTestStatus_513280(p, 0x18) != 0 && p->f4F != 0 &&
                            insect_InsectPieceCanActThunk_514920(p) != 0) {
                            if (p->f41 <= 0) {
                                insect_InsectPieceClearStatus_513340(p, 0x18);
                                p->f4C = p->f39 * 5 + 0x32;
                                insect_InsectPieceUseSpecialCharge_512c80(p);
                                Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(p20, 0x48)),
                                            p->f5C);
                                insect_InsectBattlePieceSetDesignVisible_50fa80(insect_InsectBattleGetPieceModel_50df60(o, p),
                                                    p, 0);
                                insect_InsectBattlePieceResetMotion_50f960(p);
                            } else {
                                Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(p20, 0x47)),
                                            p->f5C);
                            }
                            insect_InsectBattleLogPush_51c2f0(p22, buf, -5, -1, 0);
                        }
                    }
                    if (p->f38 == 0x11) {
                        if (insect_InsectPieceTestStatus_513280(p, 0x19) != 0 && p->f4F != 0 &&
                            insect_InsectPieceCanActThunk_514920(p) != 0 && p->f41 <= 0) {
                            insect_InsectPieceClearStatus_513340(p, 0x19);
                            insect_InsectPieceAttachSubModel_515210(p, insect_D_00524EC0);
                            insect_InsectBattlePieceSetDesignVisible_50fa80(insect_InsectBattleGetPieceModel_50df60(o, p), p, 0);
                            insect_InsectBattlePieceResetMotion_50f960(p);
                            Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(p20, 0x49)),
                                        p->f5C);
                            insect_InsectBattleLogPush_51c2f0(p22, buf, -5, -1, 0);
                        }
                    }
                    if (insect_InsectPieceTestStatus_513280(p, 0) != 0) {
                        insect_InsectBattlePoisonTick_50f220(p);
                    }
                    if (insect_InsectPieceTestStatus_513280(p, 1) != 0) {
                        if (p->f3D <= 0) {
                            insect_InsectBattleStatusCureDizzy_4f1830(o, p);
                        }
                        insect_InsectBattlePieceResetMotion_50f960(p);
                    }
                    if (insect_InsectPieceTestStatus_513280(p, 4) != 0) {
                        if (p->f40 <= 0) {
                            insect_InsectBattleStatusCureFlip_4f1790(o, p);
                        }
                        insect_InsectBattlePieceFlipMotionMaybe_50f2a0(p);
                    }
                    if (insect_InsectPieceTestStatus_513280(p, 3) != 0) {
                        if (p->f3F <= 0) {
                            insect_InsectBattleStatusCureSick_4f1700(o, p);
                        }
                    }
                    if (insect_InsectPieceTestStatus_513280(p, 6) != 0) {
                        if (p->f42 <= 0) {
                            insect_InsectPieceClearStatus_513340(p, 6);
                        }
                    } else if (insect_InsectPieceTestStatus_513280(p, 0x22) == 0) {
                        insect_InsectBoardFindPiece_4ee190(o->f4960, p, &x, &y);
                        if ((o->f4A9B[y][x] & 8) != 0 && p->f38 != 0x12) {
                            insect_InsectPieceSetStatus_5132d0(p, 6);
                            p->f42 = (((o->f4B04[y][x] & 0xF0) >> 4) + 1) / 2;
                        }
                    }
                    if (insect_InsectPieceCanActThunk_514920(p) != 0) {
                        insect_InsectPieceClearStatus_513340(p, 0x1C);
                        insect_InsectPieceClearStatus_513340(p, 0x26);
                        insect_InsectPieceClearStatus_513340(p, 0x27);
                    }
                }
            }
        }
        insect_InsectBattleSetState_50d8c0(o, 1, 5, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 0xA:
        m = 0;
        k = 0x10;
        if (o->f5EF1 == 1) {
            m = 1;
        }
        if (insect_InsectBattleTestFlag_50da40(o, m) != 0) {
            k = 0x11;
        }
        insect_InsectBattleSetState_50d8c0(o, k, 0, -1);
        if (o->f5DA8 == 0) {
            if (insect_InsectBattleTestFlag_50da40(o, 0x10) != 0) {
                insect_InsectBattleClearFlag_50da90(o, 0x10);
            } else if (o->f5EF1 == 1) {
                n = insect_InsectBattlePickTurnStartVoiceOffset_4f0130(o) + 7;
                insect_InsectBattleVoiceIdSplit_4f0220((F220Quad *)&q, o, o->f5B08[o->f5B14][n]);
                {
                    QPun qu __attribute__((aligned(16)));
                    qu.i = (s32)&q;
                    w = *qu.p;
                }
                LiveTalkVoicePlay_2070f0(w.a, w.b, w.c, w.d);
            }
        }
        insect_InsectBattleSetFlag_50dad0(o, 0x35);
        break;
    }
}
