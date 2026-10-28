/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMoveSeqStep_4fa680 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FA680 -- 1,028 bytes.  MATCHING (ix33).
 *
 * ix27 parked this at 6 bad and filed it, with insect_InsectBattleMenuActionCmd_4fd470 and
 * insect_InsectSeqExecHeraculesCrash_517120, as "a scheduler tie-break -- enumerate, record, stop."
 * THAT VERDICT IS REFUTED HERE.  The whole residue was three identical
 * two-instruction transpositions, one at each call of insect_InsectPieceMoveTo_5157d0,
 * with every float ARGUMENT REGISTER already correct and only the ORDER of
 * two argument-setup loads wrong:
 *
 *     retail  lwc1 $f15,-31128($gp)  then  lwc1 $f14,96($sp)
 *     ours    lwc1 $f14,96($sp)      then  lwc1 $f15,-31128($gp)
 *
 * *** THE CALLEE PROTOTYPE IS THE LEVER (levers.d/mwcc-prototype-param-order).
 * Integer arguments fill a0-a3,t0-t3 and float arguments $f12-$f19 from TWO
 * INDEPENDENT COUNTERS, so moving the `s32` parameter through the float list
 * cannot change which register any argument lands in -- it changes only the
 * order mwcc emits the setup.  Written `(Ent *e, s32 k, f32, f32, f32, f32)`
 * the unit is 6 bad; with the int LAST it is byte-identical.
 *
 * The lattice is (k_e, k_k) = how many floats precede each integer parameter,
 * 15 register-neutral cells.  ONLY k_k == 4 matters: (0,4) (1,4) (2,4) (3,4)
 * are ONE object and MATCH; every k_k < 4 is 6; (4,4) -- the pointer after
 * the floats too -- is 2.  So the discriminator is a SINGLE PARAMETER'S
 * POSITION, exactly as the lever predicts, and a coarse sweep finds it.
 *
 * ix27 measured 18 cells (the .lit4 literal as a per-site 2^3 lattice, three
 * extern declarations, named locals at every position) and none of them was
 * the callee's signature.
 */
#include "types.h"
/* insect 0x004FA680 -- 1,028 bytes, 260 instructions, 36 calls, 23 conditional
 * branches.  The insect_InsectBattleGetStep_50d6a0(o, 3) state-dispatch family.
 *
 * The dispatch is a beql CHAIN testing 0xD, 0xC, 0x29, 0x28, 0x2B, 0x2A, 0x27,
 * 0x26, 1 so the SOURCE order is the reverse -- 1, 0x26, 0x27, 0x2A, 0x2B,
 * 0x28, 0x29, 0xC, 0xD -- and the arm addresses (4FA774, 4FA804, 4FA854,
 * 4FA880, 4FA91C, 4FA9A4, 4FA9F0, 4FAA1C, 4FAA48) run forwards in exactly
 * that order.  Every arm is entered with $4 already loaded from the beql delay
 * slot, which is what names each arm's first callee argument.
 *
 * The two 12-byte clears are the written-out byte loop with the null check
 * (insect_FUN_004F52A0's body), u32 counter for the `bnez` at the bottom.
 * v58 is declared BEFORE v48 because mwcc gives LATER declarations LOWER
 * addresses, and both 12-byte objects are padded to 16 without being aligned.
 */

typedef struct Ent { u8 pad00[4]; } Ent;

typedef struct Obj {
    u8   pad0000[0x4960];
    u8   f4960[0x5B1C - 0x4960];        /* +0x4960 */
    Ent *f5B1C;                         /* +0x5B1C */
} Obj;

extern f32 D_0047D7D8;                  /* _gp - 0x7998 */

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

void insect_InsectBattleMoveSeqStep_4fa680(Obj *o)
{
    s32  i1;
    s32  i2;
    f32  v58[3];
    f32  v48[3];
    u8  *g;
    Ent *e;
    u8  *p;
    u32  n;

    e = o->f5B1C;
    if (e == 0) {
        return;
    }
    g = o->f4960;
    p = (u8 *)v58;
    n = 0xC;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    p = (u8 *)v48;
    n = 0xC;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    switch (insect_InsectBattleGetStep_50d6a0(o, 3)) {
    case 1:
        insect_InsectBattleClearFlag_50da90(o, 0x20);
        insect_InsectBattleClearFlag_50da90(o, 0x21);
        insect_InsectBoardFindPiece_4ee190(g, e, &i1, &i2);
        insect_InsectPieceFaceCell_515590(e, (f32)i1, (f32)i2, 4.0f);
        if (insect_InsectPieceTestStatus_513280(e, 0x22) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x26, 3, -1);
        } else {
            insect_InsectBattleSetStep_50d7a0(o, 0x2A, 3, -1);
        }
        break;
    case 0x26:
        insect_InsectPieceGetPos_5150d0(e, v58, 0, 0);
        v58[1] = 23.0f;
        insect_InsectPieceMoveTo_5157d0(e, 1, v58[0], v58[1], v58[2], D_0047D7D8);
        insect_InsectBattleSetStep_50d7a0(o, 0x27, 3, -1);
        break;
    case 0x27:
        if (insect_InsectPieceIsMoveDone_514a20(e) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x2A, 3, -1);
        }
        break;
    case 0x2A:
        if (((unsigned char)insect_InsectPieceIsTurnDone_5149f0(e)) != 0) {
            insect_InsectPlaySe_510870(4);
            insect_InsectBoardPieceWorldPos_4edad0(g, e, &v48[0], &v48[1], &v48[2]);
            if (insect_InsectPieceTestStatus_513280(e, 0x22) != 0) {
                v48[1] = 23.0f;
            }
            insect_InsectPieceMoveTo_5157d0(e, 1, v48[0], v48[1], v48[2], D_0047D7D8);
            insect_InsectBattleSetStep_50d7a0(o, 0x2B, 3, -1);
            insect_InsectPieceSetBaseMotion_5153e0(e, 1, 0, -1, 0);
        }
        break;
    case 0x2B:
        if (insect_InsectPieceIsMoveDone_514a20(e) != 0 && ((unsigned char)insect_InsectPieceIsTurnDone_5149f0(e)) != 0) {
            insect_InsectStopSe_510820(4);
            insect_InsectPieceSetBaseMotion_5153e0(e, 0, 0, -1, 0);
            if (insect_InsectPieceTestStatus_513280(e, 0x22) != 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0x28, 3, -1);
            } else {
                insect_InsectBattleSetStep_50d7a0(o, 0xC, 3, -1);
            }
        }
        break;
    case 0x28:
        insect_InsectBoardPieceWorldPos_4edad0(g, e, &v48[0], &v48[1], &v48[2]);
        insect_InsectPieceMoveTo_5157d0(e, 1, v48[0], v48[1], v48[2], D_0047D7D8);
        insect_InsectBattleSetStep_50d7a0(o, 0x29, 3, -1);
        break;
    case 0x29:
        if (insect_InsectPieceIsMoveDone_514a20(e) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xC, 3, -1);
        }
        break;
    case 0xC:
        insect_InsectPieceSetYawTarget_5156d0(e, 0.0f, 4.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0xD, 3, -1);
        break;
    case 0xD:
        if (((unsigned char)insect_InsectPieceIsTurnDone_5149f0(e)) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 3, -1);
        }
        break;
    }
}
