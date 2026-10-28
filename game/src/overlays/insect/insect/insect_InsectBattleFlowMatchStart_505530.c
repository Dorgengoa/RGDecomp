/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowMatchStart_505530 1
#include "port/game_protos.h"
#line 1
/* MATCHED, ix84 (session 84).  0 bad of 393 words, exact length 0x624,
 * frame 0x80.  From the ix81 park by ONE added declaration and a rename.
 *
 * ★★★★★★★★ THE LEVER: **GIVE THE SECOND LOOP NEST ITS OWN COUNTER.**
 * This function has two `for (i...) for (j...)` nests.  Retail colours BOTH
 * the same way -- outer counter $s4, outer body pointer $s3, register number
 * DECREASING with nesting depth -- and ix81 proved with all 120 permutations
 * of the interfering group {p,i,j,n,e} that NO single declaration order gets
 * both: the 120 collapse to exactly TWO mirror objects (9 bad and 18 bad),
 * split on whether `p` precedes `i`, because one shared `i` ties the two
 * nests' web-creation order together.  The whole 9-bad residue was a pure
 * $s3 <-> $s4 transposition in the SECOND nest only (vram 0x005059F4,
 * 0x00505A10, 0x00505A1C, 0x00505A24, 0x00505A2C, 0x00505A34, 0x00505A98,
 * 0x00505A9C, 0x00505AA0); the first nest was already byte-exact.
 *
 * Declaring a SECOND counter `i2` and using it in the second nest DECOUPLES
 * the two nests, so each one's creation order can be set independently -- and
 * the second nest then wants its counter created BEFORE the body pointer.
 * ⚠ THE DECL POSITION IS LOAD-BEARING, AND IT IS A THRESHOLD, NOT A SLOT:
 * `i2` anywhere in the first FOUR positions (before `u8 *p;`) gives the SAME
 * matching object; at `p` or later every position gives the ix81 object
 * unchanged at 9 bad (build/ix84/ins/I1_i2_at0..at8).  ONLY "before p"
 * matters, not where.  It costs nothing: 393 words either way.
 *
 * => generalisation, worth trying on any unit whose residue is a register
 * transposition confined to ONE of several loops sharing a counter:
 * [[levers.d/mwcc-gpr-decl-order-map]] says sweep the interfering group as a
 * block, but if the group spans two loops a permutation moves BOTH.  SPLIT
 * THE SHARED VARIABLE FIRST, then order each loop's group on its own.
 *
 * ALSO MEASURED HERE (build/ix84/ins/H*), all inert or worse: the address
 * expression as two statements (`p = (u8 *)o; p += ...`, 10), its operand
 * order (`+ 0x35F8 + i * 0x994`, == base), the assignment written inside the
 * call's argument list (== base), `(u32)i` on the index (== base), and
 * `(u8 *)(i * 0x994 + 0x35F8) + (s32)o` (10).  Declaring the pointer in the
 * loop's INNER SCOPE is ONE WORD SHORT (392).
 *
 * ⚠ `q` IS DELIBERATELY DECLARED 12 BYTES WIDE (Q12) WITH `qu` IMMEDIATELY
 * AFTER IT -- carried unchanged from the ix81 park and still load-bearing.
 * QPun is an aggregate and mwcc reserves a frame slot for it above the
 * existing ones; this frame's aggregate area is exactly full (`w` 16 B,
 * `q` 16 B, frame 0x80), so a 16-byte `q` plus the union gives 0x90 and two
 * bad words.  Q12 + QPun occupy ONE 16-byte region, insect_InsectBattleVoiceIdSplit_4f0220
 * writes 16 bytes across both, and `qu` is never read from memory.
 * The union pun itself is [[levers.d/mwcc-union-address-pun]]; see
 * insect_InsectBattleFlowTurnStart_508b30.c for its full account.
 */
#include "types.h"
/* insect 0x00505530 -- 1,572 bytes, 396 instructions, 54 calls, 39 conditional
 * branches.  The insect_InsectBattleGetStep_50d6a0(o, K) state-dispatch family again; the
 * header model is insect_InsectBattleMenuEndTurn_4fda60.c / insect_InsectBattleMenuPieceCmd_501810.c.
 *
 * No jump table -- a compare CHAIN testing 0xB, 0xA, 0x10, 0xF, 2, 1, so the
 * SOURCE case order is the REVERSE: 1, 2, 0xF, 0x10, 0xA, 0xB.  The block
 * addresses run 0x5055A8, 0x505884, 0x5058C4, 0x5058EC in exactly that order,
 * which is the cross-check.  Case 0xF FALLS THROUGH into case 0x10 (its last
 * instruction 0x5058E8 `lw $2, 0x5DA8($16)` is case 0x10's own beql delay
 * slot).  Cases 0xA/0xB share an empty body -- 3 words each.
 *
 * The 0x994-strided slot array at +0x35F8 is the byte-pointer spelling
 * `(u8 *)o + i * 0x994 + 0x35F8`, exactly as in the merged 004fda60.  In the
 * FIRST loop retail hoists only `o + i * 0x994` and rematerialises the
 * `addiu ..,0x35F8` every inner iteration, so the expression stays INLINE; in
 * the SECOND loop a call (00513540) sits between the two, so the whole address
 * is parked in a callee-saved register and is a NAMED local.
 *
 * The e->f4FC/f518/f4F0/f534 block is the merged main-image idiom from
 * src/s18M3/CharaDataNodeBuild_1eee10.cpp: `(s32)((u8 *)h + 0xB0A4)` and
 * `func_1D07B0((s32)h)`.
 *
 * The tail of case 0x10 is insect_InsectBattleVoiceIdSplit_4f0220's 16-byte quad written into a
 * SECOND local and passed as four scalars -- byte-for-byte the shape merged at
 * 0x004FCA7C (insect_InsectBattleMenuResultBanner_4fc780).  The PS2 EABI puts the three s32 in
 * $4/$5/$6 and the f32 in $f12.
 */

typedef struct F220Quad {
    s32 a;                          /* +0x00 */
    s32 b;                          /* +0x04 */
    s32 c;                          /* +0x08 */
    f32 d;                          /* +0x0C */
} F220Quad;

typedef union QPun { F220Quad *p; s32 i; } QPun;
typedef struct Q12 { s32 a; s32 b; s32 c; } Q12;

typedef struct Card {
    u8 pad00[0x8];
    s8 f08;                         /* +0x08 */
    s8 f09;                         /* +0x09 */
    s8 f0A;                         /* +0x0A */
    s8 f0B;                         /* +0x0B */
} Card;

typedef struct Ent {
    u8  pad000[0x4F0];
    s32 f4F0;                       /* +0x04F0 */
    u8  pad4F4[0x4FC - 0x4F4];
    s32 f4FC;                       /* +0x04FC */
    u8  pad500[0x518 - 0x500];
    s32 f518;                       /* +0x0518 */
    u8  pad51C[0x534 - 0x51C];
    s32 f534;                       /* +0x0534 */
} Ent;

typedef struct Ins {
    u8    pad000[0x870];
    void *f870;                     /* +0x0870 */
    u8    pad874[0x35F0 - 0x874];
    s32   f35F0;                    /* +0x35F0 */
    u8    pad35F4[0x4F90 - 0x35F4];
    u8    f4F90[0x4FBC - 0x4F90];   /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x5B08 - 0x4FBD];
    s32 (*f5B08)[12];               /* +0x5B08 */
    u8    pad5B0C[0x5B14 - 0x5B0C];
    s32   f5B14;                    /* +0x5B14 */
    u8    pad5B18[0x5DA8 - 0x5B18];
    s32   f5DA8;                    /* +0x5DA8 */
    u8    pad5DAC[0x5EF1 - 0x5DAC];
    u8    f5EF1;                    /* +0x5EF1 */
    u8    pad5EF2[0x5EF8 - 0x5EF2];
    s32   f5EF8;                    /* +0x5EF8 */
    u8    pad5EFC[0x5F00 - 0x5EFC];
    s16   f5F00;                    /* +0x5F00 */
} Ins;

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

void insect_InsectBattleFlowMatchStart_505530(Ins *o)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Q12)]; char m1[0x10]; })];
    QPun     qu __attribute__((aligned(16)));
    F220Quad w __attribute__((aligned(16)));
    Card *c2;
    Card *c3;
    Ent  *e;
    s32   i2;
    u8   *p;
    s32   n;
    s32   k;
    s32   i;
    s32   j;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        if (insect_InsectBattleTestFlag_50da40(o, 2) == 0) {
            insect_InsectBattleSetFlag_50dad0(o, 0x38);
        }
        if (insect_InsectBattleTestFlag_50da40(o, 3) != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0x23, 0, -1);
        } else {
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 5; j++) {
                    e = ((Ent *)insect_InsectBattleGetPieceModel_50df60(o,
                        ((s32)insect_InsectTeamGetPiece_5138d0((u8 *)o + i * 0x994 + 0x35F8, j))));
                    if (e != 0) {
                        e->f4FC = o->f35F0;
                        e->f518 = (s32)((u8 *)o->f870 + 0xB0A4);
                        e->f4F0 = GameSceneSoundSlot1GetHandle_1d07b0((s32)o->f870);
                        e->f534 = 0;
                    }
                }
            }
            if (o->f5DA8 != 0) {
                if (insect_InsectBattleTestFlag_50da40(o, 0x46) == 0) {
                    if (insect_InsectBattleTestFlag_50da40(o, 0x38) != 0) {
                        insect_InsectBattleClearFlag_50da90(o, 0x1E);
                        o->f5EF8 = 0x11;
                        switch (o->f5DA8) {
                        case 3:
                            if (o->f5EF1 == 0) {
                                o->f5EF1 = 1;
                                insect_InsectBattleSetState_50d8c0(o, 0x22, 0, -1);
                                if (o->f5EF1 != 0) {
                                    o->f4FBC = o->f4FBC | 1;
                                } else {
                                    o->f4FBC = o->f4FBC & 0xFE;
                                }
                                return;
                            } else {
                                o->f5EF1 = 0;
                            }
                            break;
                        }
                    }
                    if (o->f5DA8 == 3) {
                        insect_InsectBattleSetState_50d8c0(o, 0x27, 0, -1);
                        return;
                    }
                }
            }
            if (o->f5EF1 != 0) {
                o->f4FBC = o->f4FBC | 1;
            } else {
                o->f4FBC = o->f4FBC & 0xFE;
            }
            switch (o->f5DA8) {
            case 0:
                insect_InsectBattleSetFlag_50dad0(o, 1);
                break;
            case 3:
                break;
            case 4:
                if (insect_InsectBattleTestFlag_50da40(o, 0xE) != 0) {
                    insect_InsectBattleSetFlag_50dad0(o, 0);
                }
                insect_InsectBattleSetFlag_50dad0(o, 1);
                break;
            case 5:
                insect_InsectBattleSetFlag_50dad0(o, 0);
                insect_InsectBattleSetFlag_50dad0(o, 1);
                break;
            }
            BgmPlayTrackIfChangedMaybe_207880(0, 1);
            insect_InsectPlayJingle_510760(0x326);
            insect_InsectBattleSetState_50d8c0(o, 0x10, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            c2 = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 2));
            c3 = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 3));
            c3->f08 = c2->f08;
            c3->f09 = c2->f09;
            c3->f0A = c2->f0A;
            c3->f0B = c2->f0B;
            o->f4FBC = o->f4FBC | 0x40;
        }
        break;
    case 2:
        if (insect_InsectIsJingleDoneMaybe_510780() != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
        }
        break;
    case 0xF:
        BgmPlayTrackIfChangedMaybe_207880(0x4E, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x10, 0, -1);
        o->f5EF1 = 1;
        /* fall through */
    case 0x10:
        if (o->f5DA8 == 0) {
            k = 0;
            if (insect_InsectStoryIsRankCleared_510710() != 0) {
                insect_InsectBattleSetFlag_50dad0(o, 0x10);
                o->f5EF1 = 0;
                k = 2;
                n = ((short)insect_InsectStoryGetRankTierMaybe_510420());
                if (n >= 7) {
                    k = 3;
                }
                if (n >= 8) {
                    k = 4;
                }
            } else {
                o->f5EF1 = 1;
                if (o->f5F00 != 0) {
                    if (insect_InsectStoryIsMatchBeatenMaybe_510470() != 0) {
                        k = 2;
                    } else if (insect_InsectStoryIsRetryMaybe_510480() != 0) {
                        k = 1;
                    }
                }
            }
            insect_InsectBattleVoiceIdSplit_4f0220((F220Quad *)&(*(Q12 *)(rgp_blk1 + 0x0)), o, o->f5B08[o->f5B14][k]);
            qu.i = (s32)&(*(Q12 *)(rgp_blk1 + 0x0));
            w = *qu.p;
            LiveTalkVoicePlay_2070f0(w.a, w.b, w.c, w.d);
        }
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            if (insect_InsectBattleTestFlag_50da40(o, 0x47) != 0) {
                o->f5EF1 = 0;
            }
        }
        for (i2 = 0; i2 < 2; i2++) {
            p = (u8 *)o + i2 * 0x994 + 0x35F8;
            insect_InsectTeamMarkAllActed_513540(p, o->f5EF1);
            for (j = 0; j < 5; j++) {
                n = ((s32)insect_InsectTeamGetPiece_5138d0(p, j));
                if (n != 0) {
                    e = ((Ent *)insect_InsectBattleGetPieceModel_50df60(o, n));
                    if (e != 0) {
                        e->f4FC = insect_InsectBattleGetSoundBank_50db50(o);
                        e->f518 = (s32)((u8 *)o->f870 + 0xB0A4);
                        e->f4F0 = GameSceneSoundSlot1GetHandle_1d07b0((s32)o->f870);
                        e->f534 = 0;
                    }
                }
            }
        }
        insect_InsectBattleSetState_50d8c0(o, 0x12, 0, -1);
        insect_InsectBattleSetFlag_50dad0(o, 0xB);
        insect_InsectBattleSetFlag_50dad0(o, 0xC);
        insect_InsectBattleSetFlag_50dad0(o, 0x1A);
        insect_InsectBattleSetFlag_50dad0(o, 0x24);
        insect_InsectBattleSetFlag_50dad0(o, 0x25);
        insect_InsectBattleSetFlag_50dad0(o, 0xD);
        insect_InsectBattleSetFlag_50dad0(o, 0x27);
        if (insect_InsectBattleTestFlag_50da40(o, 0x38) != 0) {
            insect_InsectBattleSetFlag_50dad0(o, 0x26);
        }
        break;
    case 0xA:
    case 0xB:
        break;
    }
}
