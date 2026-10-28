/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCamUpdate_4f2100 1
#include "port/game_protos.h"
#line 1
/* MATCHED -- byte-identical (945 words, len 0xEC4), INSECT session 88
 * (2026-09-15).  From the ix87 park by FIVE source edits, all of them one
 * class: WHERE A FLOAT TEMP'S WEB IS CREATED, and how wide the group of
 * simultaneously live temps is.
 *
 * 1. THE 2-ELEMENT AGGREGATE COPY IS THE FILL LEVER, not the 3+1 split.
 *    `*(V2 *)a = *(V2 *)&D_x;` x2 per array.  The ix71 park's
 *    "the AGGREGATE-FILL lever on all ten gp-table -> local fills is a
 *    measured null (7 in index order, 10-17 in every aggregate form)" is
 *    RETRACTED: ix71 measured 3+1 splits and V4 copies only.  V2 pairs took
 *    case 1 (a1/b1) 7 -> 0, case 8 3 -> 0 and case 16 6 -> 0, and RECOVERED
 *    ONE OF THE TWO WORDS ix87 proved were scheduler-strength nops.
 * 2. case 18: `k` FIRST, then the fill.  A 4-element fill whose middle is cut
 *    by an integer statement comes out batched (L,L,L,S,S,S) when the integer
 *    statement is inside it and pipelined when it is above it.
 * 3. case 3: `v[0] = w[0];` BEFORE `v[2] = w[2];` -- the FPR pair swaps with
 *    creation order even though the STORE order is unchanged.
 * 4. case 18: `ang = D_0047D1FC * (f32)(s32)k;` AFTER both `* o->f5FC8`
 *    multiplies.  Creation order picks the FPR GROUP: the earlier group gets
 *    the higher registers ({f5,f4,f3} then {f2,f1}), so retail's ang pair
 *    sitting LOW says its statement is LAST.
 *    [[levers.d/mwcc-fpr-decl-order-highest-first]]
 * 5. case 4: `ax = r[0]*nc - r[1]*s;` then `ax = ax * 5.0f;` (the split ix87
 *    measured as WORSE on the old base: it is only a win once (1)-(4) are in)
 *    and `d = (d < 0.0f) ? -d : d;` for the last two words -- the TERNARY
 *    emits `bc1f` + an EMPTY slot where the one-sided `if` emits `bc1fl` with
 *    the join's `lwc1` duplicated into the annulled slot.
 *    [[levers.d/mwcc-branch-likely-duplication]]
 *
 * Record: build/ix88/FINDINGS.md.  Arms: build/ix88/ins/run{E,F,G,H,I,J,K,L,M,N,O}.py.
 */
#include "types.h"
typedef struct V2 { f32 x, y; } V2;
typedef struct V3 { f32 x, y, z; } V3;
typedef struct V4 { f32 x, y, z, w; } V4;
/* insect 0x004F2100 -- 3,780 bytes, 945 instructions, 68 calls, 49 conditional
 * branches, no jalr, no divide trap.  ix24e2.
 *
 * The state machine behind insect_jtbl_00524BD0: 19 entries, source arm order read
 * off the TARGET ADDRESSES (1 2 3 10 13 8 4 5 11 12 6 7 14 15 16 17 18).
 * Entry 9 points at the JOIN, so `case 9:` exists with an empty body; entry 0
 * points at the default block.
 *
 * `_gp = 0x00485170`.  Everything at 0x0047Dxxx is the main float pool,
 * everything at 0x00480Fxx is a real small-data table.
 *
 * The 16-byte / 8-byte clears are the image-wide `sb` do-while with the null
 * test on a frame address mwcc cannot fold and an UNSIGNED counter.
 *
 * The `mula.s/msub.s/mula.s/madd.s` quad at 004F2974 is plain C
 * `a*nc - b*s` / `b*nc + a*s` -- see [[ps2-float-accumulator]].
 */

typedef struct Obj {
    f32 f00[4];                         /* +0x0000 */
    f32 f10[4];                         /* +0x0010 */
    u8  pad20[0xA8 - 0x20];
    f32 fA8;                            /* +0x00A8 */
    u8  padAC[0xB8 - 0xAC];
    f32 fB8;                            /* +0x00B8 */
    u8  padBC[0x4960 - 0xBC];
    u8  m4960[0x4F90 - 0x4960];         /* +0x4960 */
    u8  m4F90[0x5B20 - 0x4F90];         /* +0x4F90 */
    s32 f5B20;                          /* +0x5B20 */
    s32 f5B24;                          /* +0x5B24 */
    u8  pad5B28[0x5D98 - 0x5B28];
    f32 f5D98;                          /* +0x5D98 */
    u8  pad5D9C[0x5EF1 - 0x5D9C];
    u8  f5EF1;                          /* +0x5EF1 */
    u8  pad5EF2[0x5EF8 - 0x5EF2];
    s32 f5EF8;                          /* +0x5EF8 */
    u8  pad5EFC[0x5FC8 - 0x5EFC];
    f32 f5FC8;                          /* +0x5FC8 */
} Obj;

extern f32 D_0047D1FC;                  /* _gp - 0x7F74, PI */
extern s64 D_0047D1B0;                  /* _gp - 0x7FC0 */
extern f32 D_0047D404;                  /* _gp - 0x7D6C */
extern f32 D_0047D53C;                  /* _gp - 0x7C34 */
extern f32 D_0047D5D0;                  /* _gp - 0x7BA0 */
extern f32 D_0047D8B0;                  /* _gp - 0x78C0 */
extern f32 D_0047D8B4;                  /* _gp - 0x78BC */
extern f32 D_0047D8C0;                  /* _gp - 0x78B0 */
extern f32 D_0047D8C4;                  /* _gp - 0x78AC */
extern f32 D_0047D8C8;                  /* _gp - 0x78A8 */
extern f32 D_0047D8CC;                  /* _gp - 0x78A4 */
extern f32 D_0047D8D0;                  /* _gp - 0x78A0 */

extern f32 D_00480F40;                  /* _gp - 0x4230 */
extern f32 D_00480F44;
extern f32 D_00480F48;
extern f32 D_00480F4C;
extern f32 D_00480F50;
extern f32 D_00480F54;
extern f32 D_00480F58;
extern f32 D_00480F5C;
extern f32 D_00480F60;
extern f32 D_00480F64;
extern f32 D_00480F68;
extern f32 D_00480F6C;
extern f32 D_00480F70;
extern f32 D_00480F74;
extern f32 D_00480F78;
extern f32 D_00480F7C;
extern f32 D_00480F80;
extern f32 D_00480F84;
extern f32 D_00480F88;
extern f32 D_00480F8C;
extern f32 D_00480F90;
extern f32 D_00480F94;
extern f32 D_00480F98;
extern f32 D_00480F9C;
extern f32 D_00480FA0;
extern f32 D_00480FA4;
extern f32 D_00480FA8;
extern f32 D_00480FAC;
extern f32 D_00480FB0;
extern f32 D_00480FB4;
extern f32 D_00480FB8;
extern f32 D_00480FBC;
extern f32 D_00480FC0;
extern f32 D_00480FC4;
extern f32 D_00480FC8;
extern f32 D_00480FCC;
extern f32 D_00480FD0;
extern f32 D_00480FD4;
extern f32 D_00480FD8;
extern f32 D_00480FDC;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleCamUpdate_4f2100(Obj *o)
{
    s32  t0;                            /* $sp+0x15C */
    s32  phase;                         /* $sp+0x158 */
    s32  x1;                            /* $sp+0x154 */
    s32  y1;                            /* $sp+0x150 */
    s32  x2;                            /* $sp+0x14C */
    s32  y2;                            /* $sp+0x148 */
    f32  m[2];                          /* $sp+0x140 */
    f32  w[4] __attribute__((aligned(16)));                          /* $sp+0x130 */
    f32  v[4] __attribute__((aligned(16)));                          /* $sp+0x120 */
    f32  a1[4] __attribute__((aligned(16)));                         /* $sp+0x110 */
    f32  b1[4] __attribute__((aligned(16)));                         /* $sp+0x100 */
    f32  a10[4] __attribute__((aligned(16)));                        /* $sp+0x0F0 */
    f32  a13[4] __attribute__((aligned(16)));                        /* $sp+0x0E0 */
    f32  a8[4] __attribute__((aligned(16)));                         /* $sp+0x0D0 */
    f32  b8[4] __attribute__((aligned(16)));                         /* $sp+0x0C0 */
    f32  r[4] __attribute__((aligned(16)));                          /* $sp+0x0B0 */
    f32  q[4] __attribute__((aligned(16)));                          /* $sp+0x0A0 */
    f32  a16[4] __attribute__((aligned(16)));                        /* $sp+0x090 */
    f32  b16[4] __attribute__((aligned(16)));                        /* $sp+0x080 */
    f32  a17[4] __attribute__((aligned(16)));                        /* $sp+0x070 */
    f32  a18[4] __attribute__((aligned(16)));                        /* $sp+0x060 */
    u8  *p;
    u32  n;
    s32  h;
    u8  *g;
    s32  i;
    s32  a;
    s32  b;
    s32  px;
    s32  py;
    u8   k;
    f32  lim;
    f32  d;
    f32  e;
    f32  t;
    f32  cy;
    f32  cx;
    f32  s;
    f32  nc;
    f32  ay;
    f32  ax;
    f32  ang;

    h = insect_InsectCursorSetGetPad_511000(o->m4F90, -1);
    g = o->m4960;
    insect_InsectBattleGetState_50d6f0(o, 0);
    insect_InsectBattleGetStep_50d6a0(o, 0);
    if (h != 0) {
        p = (u8 *)w;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        w[0] = PadGetAnalogLXNorm_183af0(h);
        w[1] = PadGetAnalogLYNorm_183a50(h);
        w[2] = PadGetAnalogRXNorm_183c30(h);
        w[3] = PadGetAnalogRYNorm_183b90(h);
        p = (u8 *)v;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        if (insect_InsectBattleTestFlag_50da40(o, 0x42) != 0) {
            insect_InsectCursorSetGetCell_511a40(o->m4F90, 3, &t0, &phase);
            if ((phase >= 0) && (phase < 7)) {
                lim = 4.0f * (f32)(phase - 3) / 2.0f;
                t = o->fA8;
                d = 0.0f;
                if (t > lim) {
                    d = D_0047D8B0;
                }
                if (t < lim) {
                    d = D_0047D5D0;
                }
                d = d * o->f5FC8;
                if (d > 0.0f) {
                    e = *(volatile f32 *)&o->fA8 + d;
                    o->fA8 = e;
                    if (lim <= e) {
                        d = 0.0f;
                        o->fA8 = lim;
                    }
                }
                if (d < 0.0f) {
                    e = o->fA8 + d;
                    o->fA8 = e;
                    if (!(lim < e)) {
                        o->fA8 = lim;
                    }
                }
                o->fB8 = o->fA8;
            }
        } else {
            t = o->fA8;
            d = 0.0f;
            if (t > 0.0f) {
                d = D_0047D8B0;
            }
            if (t < 0.0f) {
                d = D_0047D5D0;
            }
            d = d * o->f5FC8;
            if (d > 0.0f) {
                e = *(volatile f32 *)&o->fA8 + d;
                o->fA8 = e;
                if (0.0f <= e) {
                    o->fA8 = 0.0f;
                    d = 0.0f;
                }
            }
            if (d < 0.0f) {
                e = o->fA8 + d;
                o->fA8 = e;
                if (!(0.0f < e)) {
                    o->fA8 = 0.0f;
                }
            }
            o->fB8 = o->fA8;
        }
        switch ((u32)o->f5EF8) {
        case 1:
            *(V2 *)a1 = *(V2 *)&D_00480F40;
            *(V2 *)&a1[2] = *(V2 *)&D_00480F48;
            *(V2 *)b1 = *(V2 *)&D_00480F50;
            *(V2 *)&b1[2] = *(V2 *)&D_00480F58;
            b1[2] = *(volatile f32 *)&b1[2] * (f32)(o->f5EF1 * -2 + 1);
            insect_InsectBattleCamSetTargetGoal_4f30c0(o, a1, 2, (f32)(s32)(12.0f / o->f5FC8));
            insect_InsectBattleCamSetEyeGoal_4f3220(o, b1, 2, (f32)(s32)(12.0f / o->f5FC8));
            o->f5EF8 = 2;
            break;
        case 2:
            insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, v[2], D_0047D8B4 * v[3], v[1]
);
            break;
        case 3:
            v[1] = 0.0f;
            v[0] = w[0];
            v[2] = w[2];
            v[3] = w[3];
            v[2] = w[2] * D_0047D8C0;
            if (PadIsHeld_183a20(h, 1) != 0) {
                v[1] = D_0047D8C4;
            } else if (PadIsHeld_183a20(h, 2) != 0) {
                v[1] = D_0047D53C;
            }
            for (i = 0; i < 4; i++) {
                v[i] = v[i] * o->f5FC8;
            }
            insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, v[2], D_0047D8C8 * v[3], v[1]
);
            break;
        case 10:
            insect_InsectBattleClearFlag_50da90(o, 0x42);
            a10[0] = D_00480F60;
            a10[1] = D_00480F64;
            a10[2] = D_00480F68;
            a10[3] = D_00480F6C;
            t = D_0047D8CC;
            v[2] = t;
            if (o->f5D98 < 0.0f) {
                v[2] = -t;
            }
            v[3] = 1.0f;
            v[2] = v[2] * o->f5FC8;
            v[3] = v[3] * o->f5FC8;
            if (insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, v[2], D_0047D8C8 * v[3], -3.0f
) != 0) {
                o->f5D98 = D_0047D1FC;
                insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                o->f5EF8 = 7;
            }
            insect_InsectBattleCamApplyTarget_4f32b0(o, a10);
            break;
        case 13:
            insect_InsectBattleClearFlag_50da90(o, 0x42);
            a13[0] = D_00480F70;
            a13[1] = D_00480F74;
            a13[2] = D_00480F78;
            a13[3] = D_00480F7C;
            t = D_0047D8D0;
            v[2] = t;
            if (o->f5D98 < 0.0f) {
                v[2] = -t;
            }
            v[3] = 1.0f;
            v[2] = v[2] * o->f5FC8;
            v[3] = v[3] * o->f5FC8;
            if (o->f5D98 != 0.0f) {
                if (insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, v[2], D_0047D8C8 * v[3], -3.0f
) != 0) {
                    o->f5D98 = 0.0f;
                    insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                    o->f5EF8 = 7;
                }
            } else {
                o->f5EF8 = 7;
            }
            insect_InsectBattleCamApplyTarget_4f32b0(o, a13);
            break;
        case 8:
            *(V2 *)a8 = *(V2 *)&D_00480F80;
            *(V2 *)&a8[2] = *(V2 *)&D_00480F88;
            *(V2 *)b8 = *(V2 *)&D_00480F90;
            *(V2 *)&b8[2] = *(V2 *)&D_00480F98;
            b8[2] = *(volatile f32 *)&b8[2] * (f32)(o->f5EF1 * -2 + 1);
            insect_InsectBattleCamSave_4f1b50(o);
            insect_InsectBattleCamSetTargetGoal_4f30c0(o, a8, 2, (f32)(s32)(12.0f / o->f5FC8));
            insect_InsectBattleCamSetEyeGoal_4f3220(o, b8, 2, (f32)(s32)(12.0f / o->f5FC8));
            o->f5EF8 = 9;
            break;
        case 4:
            a = o->f5B20;
            b = o->f5B24;
            if ((a != 0) && (b != 0)) {
                insect_InsectBoardFindPiece_4ee190(g, a, &x1, &y1);
                insect_InsectBoardFindPiece_4ee190(g, b, &x2, &y2);
                cx = (f32)(x1 + x2) / 2.0f;
                cy = (f32)(y1 + y2) / 2.0f;
                if (x1 <= x2) {
                    px = x1;
                    py = y1;
                } else {
                    px = x2;
                    py = y2;
                }
                p = (u8 *)m;
                n = 8;
                if (p != 0) {
                    do {
                        *p = 0;
                        n--;
                        p++;
                    } while (n != 0);
                }
                m[0] = cx;
                m[1] = cy;
                p = (u8 *)r;
                n = 0x10;
                if (p != 0) {
                    do {
                        *p = 0;
                        n--;
                        p++;
                    } while (n != 0);
                }
                r[0] = m[0] - (f32)px;
                r[1] = m[1] - (f32)py;
                s = Sinf_128fd0(D_0047D404);
                nc = -Cosf_128d30(D_0047D404);
                ax = r[0] * nc - r[1] * s;
                ay = r[0] * s + r[1] * nc;
                ax = ax * 5.0f;
                ay = ay * 5.0f;
                insect_InsectBattleCamGetSaved_4f1b00(o, q, 0);
                t = Atan2f_1291a8(q[0], q[2]);
                d = Atan2f_1291a8(ax, ay) - t;
                d = (d < 0.0f) ? -d : d;
                if (d > D_0047D404) {
                    ax = ax * -1.0f;
                    ay = ay * -1.0f;
                }
                insect_InsectBattleCamTargetToCell_4f2ff0(o, 2, cx, 22.5f, cy,
                                    (f32)(s32)(6.0f / o->f5FC8));
                insect_InsectBattleCamEyeToCell_4f3150(o, 2, ax + cx, 27.0f, ay + cy,
                                    (f32)(s32)(6.0f / o->f5FC8));
                o->f5EF8 = 5;
            }
            break;
        case 5:
            insect_InsectBattleCamEyeRefresh_4f2fd0(o, 2, 8.0f);
            break;
        case 11:
            insect_InsectBattleCamRestoreSaved_4f1a60(o, 1, 2, (f32)(s32)(12.0f / o->f5FC8));
            o->f5EF8 = 12;
            insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            /* fallthrough */
        case 12:
            if ((insect_InsectBattleCamEyeSettled_4f19f0(o) != 0) && (insect_InsectBattleCamTargetSettled_4f1980(o) != 0)) {
                o->f5EF8 = 3;
                insect_InsectBattleSetFlag_50dad0(o, 0x42);
            }
            insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            break;
        case 6:
            insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            break;
        case 7:
            v[3] = 1.0f;
            v[3] = v[3] * o->f5FC8;
            insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, D_0047D8C8 * v[3], 0.0f
);
            break;
        case 14:
            insect_InsectBattleCamRestoreSaved_4f1a60(o, 1, 2, (f32)(s32)(12.0f / o->f5FC8));
            o->f5EF8 = 15;
            break;
        case 15:
            insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            if ((insect_InsectBattleCamEyeSettled_4f19f0(o) != 0) && (insect_InsectBattleCamTargetSettled_4f1980(o) != 0)) {
                o->f5EF8 = 6;
            }
            break;
        case 16:
            *(V2 *)a16 = *(V2 *)&D_00480FA0;
            *(V2 *)&a16[2] = *(V2 *)&D_00480FA8;
            *(V2 *)b16 = *(V2 *)&D_00480FB0;
            *(V2 *)&b16[2] = *(V2 *)&D_00480FB8;
            insect_InsectBattleCamSetTargetGoal_4f30c0(o, a16, 2, 12.0f);
            insect_InsectBattleCamSetEyeGoal_4f3220(o, b16, 2, 12.0f);
            break;
        case 17:
            a17[0] = D_00480FC0;
            a17[1] = D_00480FC4;
            a17[2] = D_00480FC8;
            a17[3] = D_00480FCC;
            t = dptofp(dpmul(__builtin_bit_cast(double, (long long)(D_0047D1B0)), litodp(o->f5EF1 * 2 - 1)
));
            v[3] = 1.0f;
            v[2] = t;
            if (o->f5D98 < 0.0f) {
                v[2] = -t;
            }
            v[2] = v[2] * o->f5FC8;
            v[3] = v[3] * o->f5FC8;
            if ((o->f5D98 != D_0047D1FC * (f32)(s32)o->f5EF1) &&
                (insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, v[2], D_0047D8C8 * v[3], 2.0f
) != 0)) {
                o->f5D98 = D_0047D1FC * (f32)(s32)o->f5EF1;
                insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                o->f5EF8 = 6;
            }
            insect_InsectBattleCamApplyTarget_4f32b0(o, a17);
            break;
        case 18:
            k = (u8)((o->f5EF1 != 0) ^ 1);
            *(V2 *)a18 = *(V2 *)&D_00480FD0;
            a18[2] = D_00480FD8;
            a18[3] = D_00480FDC;
            v[2] = dptofp(dpmul(__builtin_bit_cast(double, (long long)(D_0047D1B0)), litodp(k * 2 - 1)
));
            if (insect_InsectBattleTestFlag_50da40(o, 0xD) == 0) {
                v[3] = 1.0f;
            }
            if (o->f5D98 < 0.0f) {
                v[2] = -v[2];
            }
            v[2] = v[2] * o->f5FC8;
            v[3] = v[3] * o->f5FC8;
            ang = D_0047D1FC * (f32)(s32)k;
            if (o->f5D98 != ang) {
                if (insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, v[2], D_0047D8C8 * v[3], 2.0f
) != 0) {
                    o->f5D98 = ang;
                    insect_InsectBattleCamOrbit_4f1bc0(o, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                    o->f5EF8 = 3;
                    insect_InsectBattleSetFlag_50dad0(o, 0x42);
                }
            } else {
                o->f5EF8 = 3;
                insect_InsectBattleSetFlag_50dad0(o, 0x42);
            }
            insect_InsectBattleCamApplyTarget_4f32b0(o, a18);
            break;
        case 9:
            break;
        default:
            v[0] = w[0];
            v[1] = w[1];
            v[2] = w[2];
            v[3] = w[3];
            break;
        }
        insect_InsectBattleCamApproach_4f1fe0(o);
        insect_InsectBattleCamApplyEye_4f3320(o, o->f00);
        insect_InsectBattleCamApplyTarget_4f32b0(o, o->f10);
    }
}
