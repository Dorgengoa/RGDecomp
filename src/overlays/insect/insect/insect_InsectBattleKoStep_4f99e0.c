#include "types.h"
/* insect 0x004F99E0 -- 936 bytes, 234 words.  MATCHED session ix28 (2026-09-02)
 * after ix22/ix23/ix24 had parked it at 29 bad as "an allocator tie-break the
 * source cannot name".  Two levers, both new to this image:
 *
 *  1. THE POINTER->INTEGER->POINTER ROUND TRIP.  `(u8 *)o + 0x5F82` written
 *     inline (or as a plain named local `q = (u8 *)o + 0x5F82;`) is COPY-
 *     PROPAGATED into an address-expression TEMP, and mwcc colours compiler
 *     temps BEFORE named locals -- it took $20, the highest free callee-saved
 *     register, and pushed j/g/i/e each down one ($19..$16).  Retail holds it
 *     in $16 = coloured LAST, i.e. as a NAMED WEB.  A second def the propagator
 *     cannot see through keeps the web:  `q = (u8 *)o + 0x5F82; q = (u8 *)(s32)q;`
 *     costs no instruction and lands the whole 5-register rotation (27 words).
 *     Measured INERT (byte-identical to the propagated form): `q = q;`,
 *     `q += 0;`, `q = q + 0;`, `q += 1; q -= 1;`, `q0 = ..; q = q0;`, `register`,
 *     a block-scoped q, six declaration positions.  Measured WRONG: `q = (u8 *)o;
 *     q += 0x5F82;` (-3 words: the copy of o coalesces with o), `q = (u8 *)o +
 *     0x5F00; q += 0x82;` (right register, +0x82 rematerialised at each use),
 *     `(u8 *)((s32)o + 0x5F82)` (54 bad: an integer add, not an address).
 *     q's DECLARATION POSITION is inert (first/mid/last one object): the web is
 *     coloured last because of what it is, not where it is declared.
 *
 *  2. `(s32)e->f6C` at the FIRST func_1CF9D0 call orders the two argument
 *     loads `lh $5 / lw $4` the way retail has them (the second call, with
 *     `+ 0x40`, already did).  `s16 k = e->f6C` is inert; `s32 k` or the cast
 *     both match; a volatile pin on the lh also matches.
 */
/* insect 0x004F99E0 -- 936 bytes, 236 instructions, 31 calls, 23 conditional
 * branches.  The insect_InsectBattleGetStep_50d6a0(o, 5) state-dispatch family.
 *
 * The dispatch is a beql CHAIN testing 0x1C, 0x1B, 1, so the SOURCE order is
 * the reverse -- 1, 0x1B, 0x1C -- and the arm addresses (4F9A4C, 4F9B24,
 * 4F9C40) run forwards in exactly that order.  Case 1 FALLS THROUGH into
 * case 0x1B: 4F9B20 is the last instruction of case 1 and 4F9B24 is the
 * case-0x1B label.
 *
 * (u8 *)o + K rather than an array member for 0x4960 / 0x506C / 0x5080 /
 * 0x5F82: retail parks all four in CALLEE-SAVED registers (the first three
 * from the prologue), which is the pointer-arithmetic spelling's behaviour --
 * the array-member spelling rematerialises at every site.  0x5178 IS
 * rematerialised at its single site, so that one stays an array member.
 *
 * `lh $5,0x6C($16)` bare at one site and `dsll32/dsra32 ..,16` at the other
 * is func_1CF9D0's parameter declared s16 with the s32 sum passed bare.
 */

typedef struct Ent {
    u8  pad00[0x1C];
    s16 f1C;                    /* +0x1C */
    u8  pad1E[0x58 - 0x1E];
    s32 f58;                    /* +0x58 */
    s32 f5C;                    /* +0x5C */
    u8  pad60[0x6C - 0x60];
    s16 f6C;                    /* +0x6C */
} Ent;

typedef struct Grp { u8 pad000[0x994]; } Grp;

typedef struct Obj {
    u8   pad0000[0x870];
    s32  f870;                          /* +0x0870 */
    u8   pad0874[0x35F8 - 0x874];
    Grp  f35F8[2];                      /* +0x35F8 */
    u8   pad4920[0x4960 - 0x4920];
    u8   f4960[0x4FBC - 0x4960];        /* +0x4960 */
    u8   f4FBC;                         /* +0x4FBC */
    u8   pad4FBD[0x506C - 0x4FBD];
    u8   f506C[0x5080 - 0x506C];        /* +0x506C */
    u8   f5080[0x5178 - 0x5080];        /* +0x5080 */
    u8   f5178[4];                      /* +0x5178 */
} Obj;

extern void  func_1343B8(void *d, s32 t, s32 v);
extern void  func_1CF9D0(s32 h, s16 v, s32 n);

extern void  insect_InsectPieceSetStatus_5132d0(Ent *e, s32 k);
extern s32   insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern void  insect_InsectPieceClearStatus_513340(Ent *e, s32 k);
extern Ent  *insect_InsectTeamGetPiece_5138d0(void *g, s32 i);
extern void  insect_InsectPieceMotionQueueClear_514320(Ent *e);
extern s32   insect_InsectPieceIsMotionDone_514280(Ent *e);
extern void  insect_InsectPiecePlayMotion_5145e0(Ent *e, s32 a, s32 b, f32 x, f32 y);
extern s32   insect_InsectMsgGet_512b70(void *p, s32 k);
extern void  insect_InsectBoardRemovePiece_4ef7f0(void *a, Ent *e);
extern void  insect_InsectBattleLogPush_51c2f0(void *p, void *t, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleEffectsSpawn_51dc30(void *g, Ent *e, s32 a, s32 b, s32 c,
                                 s32 x, s32 y, s32 d, s64 f);
extern s32   insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleClearFlag_50da90(Obj *o, s32 k);

void insect_InsectBattleKoStep_4f99e0(Obj *o)
{
    void *v4960;
    void *v506C;
    void *v5080;
    s32  ok;
    s32  j;
    Grp *g;
    s32  i;
    Ent *e;
    u8  *q;

    v4960 = o->f4960;
    v506C = o->f506C;
    v5080 = o->f5080;
    switch (insect_InsectBattleGetStep_50d6a0(o, 5)) {
    case 1:
        o->f4FBC = o->f4FBC | 2;
        insect_InsectBattleClearFlag_50da90(o, 0xB);
        for (j = 0; j < 2; j++) {
            g = &o->f35F8[j];
            for (i = 0; i < 5; i++) {
                e = insect_InsectTeamGetPiece_5138d0(g, i);
                if (e != 0) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                        if (insect_InsectPieceTestStatus_513280(e, 0x1D) != 0) {
                            insect_InsectPieceClearStatus_513340(e, 0x1B);
                        } else if (e->f1C <= 0) {
                            insect_InsectPieceSetStatus_5132d0(e, 0x1D);
                            insect_InsectPieceClearStatus_513340(e, 0x1B);
                        }
                    }
                }
            }
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 5, -1);
    case 0x1B:
        for (j = 0; j < 2; j++) {
            g = &o->f35F8[j];
            for (i = 0; i < 5; i++) {
                e = insect_InsectTeamGetPiece_5138d0(g, i);
                if (e != 0) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1D) != 0) {
                        if (insect_InsectPieceTestStatus_513280(e, 0x1E) == 0) {
                            insect_InsectPieceMotionQueueClear_514320(e);
                            if (insect_InsectPieceTestStatus_513280(e, 0x25) == 0) {
                                insect_InsectPiecePlayMotion_5145e0(e, 3, 6, 0.0f, 1.0f);
                            }
                            insect_InsectPieceSetStatus_5132d0(e, 0x1E);
                            q = (u8 *)o + 0x5F82; q = (u8 *)(s32)q;
                            func_1343B8(q,
                                        insect_InsectMsgGet_512b70(v506C, 0x46),
                                        e->f5C);
                            insect_InsectBattleLogPush_51c2f0(v5080,
                                                q, -5, -1, 0);
                        }
                    } else {
                        insect_InsectPieceClearStatus_513340(e, 0x25);
                    }
                }
            }
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 5, -1);
        break;
    case 0x1C:
        ok = 1;
        for (j = 0; j < 2; j++) {
            g = &o->f35F8[j];
            for (i = 0; i < 5; i++) {
                e = insect_InsectTeamGetPiece_5138d0(g, i);
                if (e != 0) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1E) != 0) {
                        if (insect_InsectPieceTestStatus_513280(e, 0x1F) == 0) {
                            if (insect_InsectPieceIsMotionDone_514280(e) != 0) {
                                insect_InsectPieceSetStatus_5132d0(e, 0x1F);
                                insect_InsectBattleEffectsSpawn_51dc30(o->f5178, e, 0x10, 2, 0,
                                                    -1, -1, 1, 0);
                                insect_InsectBoardRemovePiece_4ef7f0(v4960, e);
                                func_1CF9D0(o->f870, (s32)e->f6C, 0xF);
                                if (e->f58 != 0) {
                                    func_1CF9D0(o->f870, e->f6C + 0x40, 0xF);
                                }
                            } else {
                                ok = 0;
                            }
                        }
                    }
                }
            }
        }
        if (ok != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0, 5, -1);
        }
        break;
    }
}
