/* rgp:protos */
#define RGP_SELF_insect_InsectCursorSetInput_511090 1
#include "port/game_protos.h"
#line 1
/* ix80a MATCH -- insect_InsectCursorSetInput_511090, 2,332 B / 585 words, BYTE-IDENTICAL.
 * Verified twice: swx.py arm D2_13u32s_gtu32s (sha1.text 3f4e10a4, link MATCH,
 * build/ix80a/sweep_511090_gtform.log) and again from this file through
 * holdfile.py -> residue.py "0 bad" / regmap.py "0 substitutions".
 * NOT MERGED by ix80a -- the session owner merges.
 *
 * Three source facts took the ix66 park 10 -> 0 (see build/ix80a/FINDINGS.md):
 *  1. `q = (Rec *)((u32)sel + (s32)r);` as the FIRST statement INSIDE the
 *     d<0 guard block.  Its vreg is CREATED above the guard's compare, so the
 *     guard's `lb` value and its `&m08` address must avoid q's colour: that
 *     alone moves them a3/t0 (retail) instead of a2/a3, and puts q's `addu`
 *     ahead of the `t` add -- the whole 4-word 0051183C-4C rotation.
 *     [[levers.d/mwcc-vreg-creation-source-position]]
 *  2. `q` is used at EXACTLY two of the four body sites (`q->m08 += (s8)d;`
 *     and `if ((s8)q->m0A < 0)`).  One use is copy-propagated away (object
 *     == park); three or four fold the `+10` into the `sb` and empty the
 *     0051187C delay slot retail fills with `addiu $a1,$a2,10`.
 *  3. The body address is spelled `(u32)sel + (s32)r`, NOT `(u8 *)r + sel`.
 *     A POINTER `+` is canonicalised base-first (ARMED NULL, ix42b) so it can
 *     never emit retail's sel-first `addu $a2,$v1,$s0`; the plain integer
 *     `sel + (s32)r` gets the order right but CSEs with the guard and loses a
 *     word; the (u32) cast keeps `sel` source-left AND defeats that CSE.
 *     `(u32)sel + (u32)r` is the same object.
 *  ALSO: `t = ...->m08 - (-d);` pins the `t` add's operand order
 *     ([[levers.d/mwcc-commutative-add-operand-order]], measured on this unit
 *     in s42 and never crossed with the ix66 park until now).
 */
/* ix66 PARK -- EXACT LENGTH, 10 bad (was 14).  DO NOT MERGE.
 * Region 1 (switch-dispatch threading, 4 words) CLOSED: `case 4:` carries a
 * DEAD re-assignment `up = 0x1000;` (its initial value).  At threading time
 * the arm is non-empty, so case 4's dispatch branch is not a join-jump and
 * takes no copy; case 0 (last compare) gets `beql`+`move a0,s4` as retail;
 * the dead store is deleted later, length unchanged.  `right = 0x2000;`
 * instead re-colours the unit (104 bad); `flags = 0;` or all four are the
 * same object.  build/ix66/sweep_511090_ix66c_deadarm.log, swprobe2.c w7.
 * Remaining 10: region 2 caller-saved renames a2/a3/t0 + a 4-word
 * addu/lb/dsra32/ori reschedule, region 3 one addu rename (ix65 read). */
/* ix56 (session 56, solo) -- STILL 14, but the unit is no longer thirty-two
 * sessions stale: five decks, 150 arms, controls (IXCTL=insect_InsectSeqGetState_4ea340)
 * reading _pos MATCH / _neglen ? throughout.  The 14 are three groups:
 *
 *   00511134/38 + 00511160/64   WHICH empty switch arm gets the branch-likely
 *                               duplication of the join's `move $a0,$s4`
 *   00511820-5C                 a caller-saved shift ($a3/$a2, $t0/$a3)
 *   00511838-4C + 005118C8      the record address's ADDU OPERAND ORDER and
 *                               the position of `flags |= 0x10;`
 *
 * MEASURED NULLS:
 *  - deck N, THE KNOB AXIS, which this ix24 park had never seen: 10 group-A
 *    codegen switches on and off, the 7 global-optimizer names and 10 backend
 *    names level-first on and off, and levels 0-4.  61 arms, ARMED BY COMPILER
 *    ERROR (`opt_unroll_count off` = NOOBJ, and `opt_generateconditionalassign-
 *    ments on` is an INTERNAL COMPILER ERROR): 50 byte-identical, every other
 *    arm wrong length or far worse.
 *  - deck M, the switch's two empty arms (`case 0:` and `case 4:`) reordered,
 *    merged onto one label, turned into `default:`, and dropped: 9 arms, all
 *    worse or wrong length.  The branch-likely pick does not follow case order.
 *  - deck L/O, THE ADDRESS SPELLING.  The park deliberately writes the same
 *    address two ways and that is load-bearing: flipping any one
 *    `((Rec *)((u8 *)r + sel))` to `(sel + (s32)r)` lets mwcc CSE it with the
 *    `if` condition's copy in $t1 and costs 7 words or the length.  ★ AND
 *    `sel + (u8 *)r`, `sel + (s8 *)r`, `(u32)sel + (u8 *)r` are all
 *    BYTE-IDENTICAL to `(u8 *)r + sel`: **mwcc canonicalises POINTER
 *    arithmetic base-first**, while the INTEGER form `sel + (s32)r` emits
 *    sel-first -- so the two spellings are the only two orders available and
 *    neither is retail's at 00511838.  `t = d + m08` for `t = m08 + d` is
 *    likewise byte-identical.
 *  - deck P, session 55's SPLIT x DECL-SLOT CROSS: `t`'s four live ranges each
 *    split out and swept through every slot of the decl block, 52 arms, ALL
 *    BYTE-IDENTICAL to base.
 */
/* PARKED, NOT MATCHING -- do not merge.  See build/ix24/parked/insect_InsectCursorSetInput_511090.md */
#include "types.h"
/* insect 0x00511090 -- 2,332 B / 585 words.  The pad-driven cursor step of the
 * insect-cage menu.  Four direction blocks (up/down/left/right) that each move
 * a cursor byte, scroll a window byte, wrap, and record what happened both in
 * the caller's 64-bit event word o->m30 and in a local 64-bit accumulator.
 *
 * The direction MASKS are rotated by o->m60 (0..4): 0x1000/0x2000/0x4000/0x8000
 * are the pad's UP/RIGHT/DOWN/LEFT bits.
 *
 * `flags &= ~4` on a 64-bit local is retail's `addiu $2,$0,-5` + `pcpyld`
 * (2 words); the SAME clear spelled `~4u` builds the constant in three.  The
 * o->m30 clears really are the three-word unsigned form (`ori/dsll/ori`), so
 * they are spelled `~0x10000u`.  [[ix18 LEVERS: 64-bit mask]] */

typedef struct Rec {
    u8  pad00[0x8];
    s8  m08;                    /* +0x08  column cursor      */
    s8  m09;                    /* +0x09  row cursor         */
    s8  m0A;                    /* +0x0A  column window top  */
    s8  m0B;                    /* +0x0B  row window top     */
    s8  m0C;                    /* +0x0C  visible columns    */
    s8  m0D;                    /* +0x0D  visible rows       */
    s8  m0E;                    /* +0x0E  max column top     */
    s8  m0F;                    /* +0x0F  max row top        */
    s8  m10;                    /* +0x10  analogue step      */
    u8  pad11[0x7];
    s64 m18;                    /* +0x18  behaviour flags    */
} Rec;

typedef struct Obj {
    u8  pad00[0x2C];
    u8  m2C;                    /* +0x2C */
    u8  pad2D[0x3];
    s64 m30;                    /* +0x30  event word */
    u8  pad38[0x28];
    s8  m60;                    /* +0x60  rotation   */
} Obj;

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

void insect_InsectCursorSetInput_511090(Obj *o)
{
    s32 pad;
    u64 flags;
    s32 up;
    s32 down;
    Rec *r;
    s32 left;
    s32 right;
    s64 fl;
    s32 d;
    s32 sel;
    s32 t;
    s32 h;
    Rec *q;

    if (!(o->m2C & 0x20)) {
        o->m30 = 0;
    }
    if (o->m2C & 0x2) {
        return;
    }
    r = ((Rec *)insect_InsectCursorSetGetCurPage_511e20(o));
    if (r == NULL) {
        return;
    }
    pad = insect_InsectCursorSetGetPad_511000(o, -1);
    flags = 0;
    up = 0x1000;
    down = 0x4000;
    left = 0x8000;
    right = 0x2000;
    PadGetAnalogLXNorm_183af0(pad);
    PadGetAnalogLYNorm_183a50(pad);
    insect_InsectCursorSetUpdatePadRotation_510ed0(o);
    switch (o->m60) {
    case 0:
        break;
    case 1:
        up = 0x2000;
        right = 0x4000;
        down = 0x8000;
        left = 0x1000;
        break;
    case 2:
        up = 0x4000;
        right = 0x8000;
        down = 0x1000;
        left = 0x2000;
        break;
    case 3:
        up = 0x8000;
        right = 0x1000;
        down = 0x2000;
        left = 0x4000;
        break;
    case 4:
        up = 0x1000;
        break;
    }
    if (PadAnyInput_183e80(pad) != 0) {
        if (PadIsTriggered_1839f0(pad, up) != 0) {
            o->m30 |= 0x1;
            if (r->m0D > 1) {
                r->m09--;
                flags |= 0x4;
                if ((s8)r->m09 < 0) {
                    o->m30 |= 0x10000;
                    r->m09 = 0;
                    r->m0B--;
                    if ((s8)r->m0B < 0) {
                        if ((r->m18 & 0x1) && PadIsRepeatTriggered_183dd0(pad, up) == 0) {
                            r->m09 = r->m0D - 1;
                            r->m0B = r->m0F;
                            if (r->m0F == 0) {
                                if (!(r->m18 & 0x20)) {
                                    flags &= ~0x4LL;
                                }
                            }
                        } else {
                            r->m0B = 0;
                            flags &= ~0x4LL;
                            o->m30 &= ~0x10000u;
                        }
                    }
                }
            }
        } else if (PadIsTriggered_1839f0(pad, down) != 0) {
            o->m30 |= 0x2;
            if (r->m0D > 1) {
                r->m09++;
                flags |= 0x8;
                if ((s8)r->m09 >= r->m0D) {
                    o->m30 |= 0x20000;
                    r->m09 = r->m0D - 1;
                    t = r->m0B + 1;
                    r->m0B = (s8)t;
                    if (r->m0F < (s8)t) {
                        if ((r->m18 & 0x1) && PadIsRepeatTriggered_183dd0(pad, down) == 0) {
                            r->m09 = 0;
                            r->m0B = 0;
                            if (r->m0F == 0) {
                                if (!(r->m18 & 0x20)) {
                                    flags &= ~0x8LL;
                                }
                            }
                        } else {
                            r->m0B = r->m0F;
                            flags &= ~0x8LL;
                            o->m30 &= ~0x20000u;
                        }
                    }
                }
            }
        }
        if (PadIsTriggered_1839f0(pad, left) != 0) {
            o->m30 |= 0x4;
            if (r->m0C > 1) {
                r->m08--;
                flags |= 0x1;
                if ((s8)r->m08 < 0) {
                    o->m30 |= 0x40000;
                    r->m08 = 0;
                    r->m0A--;
                    if ((s8)r->m0A < 0) {
                        if ((r->m18 & 0x1) && PadIsRepeatTriggered_183dd0(pad, left) == 0) {
                            r->m08 = r->m0C - 1;
                            r->m0A = r->m0E;
                            if (r->m0E == 0) {
                                if (!(r->m18 & 0x20)) {
                                    flags &= ~0x1LL;
                                }
                            }
                        } else {
                            r->m0A = 0;
                            flags &= ~0x1LL;
                            o->m30 &= ~0x40000u;
                        }
                    }
                }
            }
        } else if (PadIsTriggered_1839f0(pad, right) != 0) {
            o->m30 |= 0x8;
            if (r->m0C > 1) {
                r->m08++;
                flags |= 0x2;
                if ((s8)r->m08 >= r->m0C) {
                    o->m30 |= 0x80000;
                    r->m08 = r->m0C - 1;
                    t = r->m0A + 1;
                    r->m0A = (s8)t;
                    if (r->m0E < (s8)t) {
                        if ((r->m18 & 0x1) && PadIsRepeatTriggered_183dd0(pad, right) == 0) {
                            r->m08 = 0;
                            r->m0A = 0;
                            if (r->m0E == 0) {
                                if (!(r->m18 & 0x20)) {
                                    flags &= ~0x2LL;
                                }
                            }
                        } else {
                            r->m0A = r->m0E;
                            flags &= ~0x2LL;
                            o->m30 &= ~0x80000u;
                        }
                    }
                }
            }
        }
        if (PadIsTriggered_1839f0(pad, 0x10) != 0) {
            o->m30 |= 0x10;
        }
        if (PadIsTriggered_1839f0(pad, 0x20) != 0) {
            o->m30 |= 0x20;
        }
        if (PadIsTriggered_1839f0(pad, 0x80) != 0) {
            o->m30 |= 0x40;
        }
        if (PadIsTriggered_1839f0(pad, 0x40) != 0) {
            o->m30 |= 0x80;
        }
        if (PadIsTriggered_1839f0(pad, 0x4) != 0) {
            o->m30 |= 0x100;
        }
        if (PadIsTriggered_1839f0(pad, 0x1) != 0) {
            o->m30 |= 0x200;
        }
        if (PadIsTriggered_1839f0(pad, 0x200) != 0) {
            o->m30 |= 0x400;
        }
        if (PadIsTriggered_1839f0(pad, 0x8) != 0) {
            o->m30 |= 0x800;
        }
        if (PadIsTriggered_1839f0(pad, 0x2) != 0) {
            o->m30 |= 0x1000;
        }
        if (PadIsTriggered_1839f0(pad, 0x400) != 0) {
            o->m30 |= 0x2000;
        }
        if (PadIsTriggered_1839f0(pad, 0x800) != 0) {
            o->m30 |= 0x4000;
        }
        if (PadIsTriggered_1839f0(pad, 0x100) != 0) {
            o->m30 |= 0x8000;
        }
        fl = r->m18;
        if ((fl & 0x4) || (fl & 0x80)) {
            d = 0;
            sel = 1;
            if (fl & 0x80) {
                if (o->m30 & 0x8) {
                    d = r->m10;
                }
                if (o->m30 & 0x4) {
                    d = -r->m10;
                }
            }
            if (fl & 0x4) {
                if (o->m30 & 0x800) {
                    d = r->m10;
                }
                if (o->m30 & 0x100) {
                    d = -r->m10;
                }
            }
            if (fl & 0x8) {
                d = -d;
            }
            if (fl & 0x40) {
                sel = 0;
            }
            if (d < 0) {
                if (((Rec *)(sel + (s32)r))->m08 > 0 ||
                    ((Rec *)(sel + (s32)r))->m0A > 0) {
                    q = (Rec *)((u32)sel + (s32)r);
                    t = ((Rec *)(sel + (s32)r))->m08 - (-d);
                    flags |= 0x10;
                    q->m08 += (s8)d;
                    if (t < 0) {
                        ((Rec *)(sel + (s32)r))->m08 = 0;
                        ((Rec *)((u32)sel + (s32)r))->m0A += (s8)t;
                        if ((s8)q->m0A < 0) {
                            ((Rec *)((u32)sel + (s32)r))->m0A = 0;
                        }
                    }
                }
            } else if (d > 0) {
                if (((Rec *)(sel + (s32)r))->m08 <
                        ((Rec *)(sel + (s32)r))->m0C - 1 ||
                    ((Rec *)(sel + (s32)r))->m0A <
                        ((Rec *)(sel + (s32)r))->m0E) {
                    ((Rec *)((u32)sel + (s32)r))->m08 += (s8)d;
                    t = (((Rec *)(sel + (s32)r))->m0C - 1) -
                        (s8)((Rec *)((u32)sel + (s32)r))->m08;
                    flags |= 0x10;
                    if (t < 0) {
                        ((Rec *)(sel + (s32)r))->m08 =
                            ((Rec *)(sel + (s32)r))->m0C - 1;
                        ((Rec *)((u32)sel + (s32)r))->m0A -= (s8)t;
                        if (((Rec *)((u32)sel + (s32)r))->m0E <
                            (s8)((Rec *)((u32)sel + (s32)r))->m0A) {
                            ((Rec *)((u32)sel + (s32)r))->m0A =
                                ((Rec *)((u32)sel + (s32)r))->m0E;
                        }
                    }
                }
            }
        }
    }
    if (!(o->m2C & 0x40) && (r->m18 & 0x2)) {
        h = GetCurrentScene_1f5be0();
        if (h != 0) {
            if (flags & 0x1F) {
                GameSceneSoundSlot0PlaySeVol_1d05f0(h, 4, 1.0f);
            }
        }
    }
}
