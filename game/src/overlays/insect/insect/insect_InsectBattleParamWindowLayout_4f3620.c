/* rgp:protos */
#define RGP_SELF_insect_InsectBattleParamWindowLayout_4f3620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F3620 -- 3,132 bytes, 783 instructions, 122 calls, 41
 * conditional branches, br/ins 0.052.  The largest non-jump-table member of
 * the branch-light BAND (x_band.py) and the biggest single unit left that is
 * not behind the jump-table plumbing.
 *
 * It is NOT in the state-dispatch family, despite memory/overlay-insect
 * listing it there: it never calls insect_InsectBattleGetStep_50d6a0.  It is a widget
 * LAYOUT builder -- one func_290460 lookup and one func_290F60 placement per
 * element -- and its callee set (func_290F60 x27, insect_InsectPieceTestStatus_513280 x17,
 * func_290460 x16) has nothing in common with the dispatch family's.
 *
 * o->m87C is re-read with `lw $4, 0x87C($19)` before EVERY call; it is not
 * hoisted into a local and must not be written as one.
 *
 * D_0047D278 / D_0047D5D0 are MAIN-image small data (_gp is 0x00485170, so
 * the gp window is 0x47D170..0x48D170 and both are inside it) and stay
 * NON-const to keep %gp_rel.  insect_D_00524B80 / insect_D_00524B98 / insect_D_00524C20 /
 * insect_D_00524C28 / insect_D_00524C30 are OVERLAY data at 0x0052xxxx, outside that
 * window, so they are const or the link dies on a GP offset overflow while
 * the object still compiles clean.
 *
 * The two id locals are u16: `ori $5, $0, 0xC35F` builds the call argument
 * and `andi $20, $5, 0xFFFF` narrows the SAME register into the variable, so
 * the assignment and the argument share one materialisation.
 *
 * insect_D_00524B80 and insect_D_00524B98 are read with lhu at a stride of FOUR, so the
 * element is a halfword every other halfword and [i * 2] on a u16 array is
 * what gives `sll $3, $20, 2`.
 *
 * MATCHED, session 24 lane ix24b1: 783 of 783 words byte-identical.
 *
 * The residue was ONE register tie-break in the SECOND loop -- retail puts the
 * Anim walker in $7 and the inner counter in $6, we had them the other way
 * round -- and the lever is SPLIT THE REUSED LOCAL (LEVERS.md section 1).
 * `a` was assigned in TWO DISJOINT live ranges, the i<6 loop and the i<3 loop,
 * which mwcc kept in ONE register.  Giving the SECOND loop its own walker
 * `a2`, declared at the HEAD of the loop-local block, flips the pair.
 * Measured: a2 first or immediately before `i` is object 52df91c9 = MATCH;
 * a2 immediately before `a`, after `a`, or last is byte-identical to the
 * 24-bad baseline 95681c21.  Merging the inner counter `j` into the already
 * dead `n` or `t` is INERT alone and reaches the same matching object when
 * paired with the split.  Splitting the FIRST loop instead is INERT.
 *
 * !! Declaration ORDER cannot see this: session 23 enumerated all 119
 * non-identity permutations of `n i j a k` and every one gave 95681c21.
 *
 * TWELVE earlier spellings all gave the identical 24 bad words and are waste:
 *   for-loop / do-while / while / `j = 0` before the i test / `j = 0` before
 *   the lookup call (33 bad -- worse) / a block-scoped counter / a separate
 *   walking pointer assigned from `a` / `a[j]` indexing (0xC4C -- longer) /
 *   `a = a + 1` instead of `a += 1` / the guard CSE'd as `w->m24 != 0` /
 *   `a` declared FIRST of all locals / `a` declared LAST.
 * `if (i != 0)` first gives 0xC34 -- shorter, so the arm order is settled.
 *
 * Everything else in this unit is SOLVED and the levers are worth keeping:
 *   - (f32) of a `u16` field needs an explicit `(s32)` cast or mwcc emits the
 *     UNSIGNED conversion (bltzl/srl/or, 8 extra words per site);
 *   - the five strcat sources are ONE `const char *sv[5]` in the frame, not
 *     five scalars -- five scalars leave three of them in $22/$23/$30 and cost
 *     two extra callee-saved registers and a bigger frame;
 *   - every widget id PARAMETER is `u16`; with `s32` mwcc re-narrows the live
 *     id at each use (`andi $21,$21,0xFFFF`);
 *   - `flag` must be declared AFTER `g` -- that one swap moved 185 bad words
 *     to 47 by putting flag in $16 and g in $17;
 *   - the clear loop's counter is UNSIGNED; a signed one gives `bgtz` where
 *     retail has `bnez`;
 *   - `k == 0xF || k == 0x10` RANGE-MERGES into `addiu -15 / sltiu 2`.  Retail
 *     does not merge, and the shape that reproduces it is a switch with the
 *     two labels SHARING one body (`case 0xF: case 0x10: flag = 1; break;`) --
 *     two separate case blocks merge BOTH bodies into branch-likely slots.
 */

typedef struct Anim {
    u8  pad00[0x8];
    s64 m8;                     /* +0x08 -- cleared with one `sd` */
    s16 m10;
    s16 m12;                    /* +0x12 */
    s16 m14;                    /* +0x14 */
    u8  pad16[0x1A - 0x16];
    s16 m1A;                    /* +0x1A */
    u8  pad1C[0x20 - 0x1C];     /* stride 0x20 -- the inner loop steps by it */
} Anim;

typedef struct Box {
    s16 m0;
    s16 m2;
    u8  pad04[0x10 - 0x4];
    s16 m10;
    s16 m12;
} Box;

typedef struct Glyph {
    u8  pad00[0x24];
    s16 m24;
    s16 m26;
    u8  pad28[0x2C - 0x28];
    s16 m2C;
    s16 m2E;
} Glyph;

typedef struct Widget {
    u8    pad00[0x20];
    Glyph *m20;                 /* +0x20 */
    Anim  *m24;                 /* +0x24 */
    Box   *m28;                 /* +0x28 */
} Widget;

typedef struct Rec {
    u8  pad00[0x18];
    s8  m18;                    /* +0x18 */
    u8  pad19[0x1A - 0x19];
    s16 m1A;                    /* +0x1A */
    u8  pad1C[0x1E - 0x1C];
    s16 m1E;                    /* +0x1E */
    u8  pad20[0x22 - 0x20];
    u16 m22;                    /* +0x22 */
    s16 m24;                    /* +0x24 */
    u8  m26;                    /* +0x26 */
    u8  pad27[0x28 - 0x27];
    u8  m28;                    /* +0x28 */
    u8  pad29[0x36 - 0x29];
    s8  m36;                    /* +0x36 */
    s8  m37;                    /* +0x37 */
    s8  m38;                    /* +0x38 */
    u8  pad39[0x5C - 0x39];
    u8  *m5C;                   /* +0x5C */
    u8  *m60;                   /* +0x60 */
    u8  *m64;                   /* +0x64 */
    u8  pad68[0x70 - 0x68];
    s8  m70;                    /* +0x70 */
} Rec;

typedef struct Ins {
    u8   pad0000[0x87C];
    void *m87C;                 /* +0x087C */
    u8   pad0880[0x5054 - 0x880];
    u8   m5054[0x18];           /* +0x5054 -- the layout handle */
    u8   m506C[0x5DA0 - 0x506C];/* +0x506C -- the record list */
    s32  m5DA0;                 /* +0x5DA0 */
    s32  m5DA4;                 /* +0x5DA4 */
    s32  m5DA8;                 /* +0x5DA8 */
    u8   pad5DAC[0x5F02 - 0x5DAC];
    u8   m5F02[0x40];           /* +0x5F02 */
    u8   m5F42[0x40];           /* +0x5F42 */
} Ins;

extern f32 D_0047D278;
extern f32 D_0047D5D0;
extern u16 insect_D_00524B80[];
extern u16 insect_D_00524B98[];
extern char insect_D_00524C20[];
extern char insect_D_00524C28[];
extern char insect_D_00524C30[];

extern void  Sprintf_1343b8(void *dst, const char *fmt, ...);
extern void  strcat(void *dst, const char *src);
extern s32   strlen(const void *s);
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

s32 insect_InsectBattleParamWindowLayout_4f3620(Ins *o, Rec *r)
{
    const char *sv[5];
    void *g;
    s32 flag;
    Widget *w;
    Glyph *gl;
    Box *b;
    u8 *q;
    u32 c;
    u8 *buf;
    u16 id20;
    u16 id21;
    s32 t;
    s32 x;
    s32 y;
    Anim *a2;
    s32 n;
    s32 i;
    s32 j;
    Anim *a;
    s8 k;

    g = o->m5054;
    if (r == 0) {
        return 0;
    }
    flag = 0;
    if (o->m5DA8 == 0 && r->m70 == 1) {
        k = r->m38;
        switch (k) {
        case 0xF:
        case 0x10:
            flag = 1;
            break;
        }
    }

    t = o->m5DA0 - 0x178;
    x = t / 2;
    t = o->m5DA4 - 0x13E;
    y = t / 2;
    UiSetWidgetPos_290f60(o->m87C, 0xC350, x, y);
    UiWindowFrameLayoutMaybe_392bb0(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC351)), 0x178, 0x13E, 1);

    if (insect_InsectPieceTestStatus_513280(r, 3) != 0) {
        id20 = 0xC35F;
        UiSetWidgetColor_2905b0(o->m87C, 0xC35F, D_0047D278, D_0047D5D0, D_0047D5D0, 1.0f);
    } else {
        id20 = 0xC35F;
        UiSetWidgetColor_2905b0(o->m87C, 0xC35F, 1.0f, 1.0f, 1.0f, 1.0f);
    }
    insect_InsectBattleClearTextBuf_50e120(o, 0);

    buf = o->m5F02;
    q = (u8 *)sv;
    c = 0x14;
    if (q != 0) {
        do {
            *q = 0;
            c -= 1;
            q += 1;
        } while (c != 0);
    }
    sv[0] = ((const char *)insect_InsectMsgGet_512b70(o->m506C, 0x1F4));
    sv[1] = ((const char *)insect_InsectMsgGet_512b70(o->m506C, 0x1F5));
    sv[2] = ((const char *)insect_InsectMsgGet_512b70(o->m506C, 0x1F6));
    sv[3] = ((const char *)insect_InsectMsgGet_512b70(o->m506C, 0x1F7));
    sv[4] = ((const char *)insect_InsectMsgGet_512b70(o->m506C, 0x1F8));

    if (insect_InsectPieceTestStatus_513280(r, 4) == 0 && insect_InsectPieceTestStatus_513280(r, 1) == 0 &&
        insect_InsectPieceTestStatus_513280(r, 3) == 0 && insect_InsectPieceTestStatus_513280(r, 0) == 0) {
        strcat(buf, sv[0]);
    } else {
        if (insect_InsectPieceTestStatus_513280(r, 0) != 0) {
            strcat(buf, sv[1]);
            if (insect_InsectPieceTestStatus_513280(r, 4) != 0 ||
                insect_InsectPieceTestStatus_513280(r, 1) != 0 ||
                insect_InsectPieceTestStatus_513280(r, 3) != 0) {
                strcat(buf, insect_D_00524C20);
            }
        }
        if (insect_InsectPieceTestStatus_513280(r, 3) != 0) {
            strcat(buf, sv[2]);
            if (insect_InsectPieceTestStatus_513280(r, 1) != 0 ||
                insect_InsectPieceTestStatus_513280(r, 4) != 0) {
                strcat(buf, insect_D_00524C20);
            }
        }
        if (insect_InsectPieceTestStatus_513280(r, 1) != 0) {
            strcat(buf, sv[3]);
            if (insect_InsectPieceTestStatus_513280(r, 4) != 0) {
                strcat(buf, insect_D_00524C20);
            }
        }
        if (insect_InsectPieceTestStatus_513280(r, 4) != 0) {
            strcat(buf, sv[4]);
        }
    }

    n = insect_InsectMsgTextWidth_512ab0(o->m506C, buf, 2);
    UiWindowFrameLayoutMaybe_392bb0(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC3A2)), 0x178, 0x24, 1);
    UiSetWidgetPos_290f60(o->m87C, 0xC3A2, 0, 0x142);
    t = 0x178 - n;
    y = t / 2;
    UiSetTextStringPos_290b20(o->m87C, 0xC3A2, buf, y, 8, 0);
    UiNineSliceLayoutMaybe_392440(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC352)), 0x6E, 0x6E);
    UiSetWidgetPos_290f60(o->m87C, 0xC352, 0x10, 8);
    UiSetWidgetPos_290f60(o->m87C, 0xC353, 0x72, 0);
    UiSetTextStringPos_290b20(o->m87C, 0xC353, r->m5C, -1, -1, 0);
    UiSetWidgetPos_290f60(o->m87C, 0xC354, 0, 0x1C);
    UiSetTextStringPos_290b20(o->m87C, 0xC354, r->m60, -1, -1, 0);

    buf = o->m5F42;
    n = strlen(r->m60);
    if (insect_InsectPieceIsAce_514ac0(r) != 0) {
        Sprintf_1343b8(buf, insect_D_00524C28);
    } else {
        Sprintf_1343b8(buf, insect_D_00524C30, r->m18);
    }
    UiSetTextStringPos_290b20(o->m87C, 0xC355, buf, -1, -1, 0);
    UiSetWidgetPos_290f60(o->m87C, 0xC355, n * 8, 0);

    w = ((Widget *)UiFindWidget_290460(o->m87C, 0xC357));
    n = insect_InsectPieceTestStatus_513280(r, 0x16);
    UiToggleIconPairLayoutRelated_392660(g, w, n, insect_InsectPieceTestStatus_513280(r, 0x17), 0, 0);
    UiIconSetUvByIndexMaybe_3925d0(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC358)), r->m36, 0, 0);
    UiSetWidgetPos_290f60(o->m87C, 0xC357, 0, 0x1F);
    UiSetWidgetPos_290f60(o->m87C, 0xC358, 0x64, -2);

    if (insect_InsectPieceIsAce_514ac0(r) != 0) {
        id21 = 0xC35B;
        UiGaugeBarLayoutMaybe_392780(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC35B)), 2, (f32)(s32)r->m22,
                    (f32)r->m24);
    } else {
        id21 = 0xC35B;
        UiGaugeBarLayoutMaybe_392780(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC35B)), 1, (f32)(s32)r->m22,
                    (f32)r->m24);
    }
    UiSetWidgetPos_290f60(o->m87C, 0xC359, 4, 0x1C);
    UiSetWidgetPos_290f60(o->m87C, id21, 0x20, 4);
    UiGaugeBarLayoutMaybe_392780(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC35D)), 0, (f32)r->m37, 100.0f);
    UiSetWidgetPos_290f60(o->m87C, 0xC35C, 0x69, -1);
    UiSetWidgetPos_290f60(o->m87C, 0xC35D, 0x34, 5);
    UiSpriteListFillColumnMaybe_3939e0(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC35E)), 7, 1, 226.0f, 28.0f);
    UiSetWidgetPos_290f60(o->m87C, 0xC35E, 0, 0x14);
    UiSetWidgetPos_290f60(o->m87C, id20, -2, 0x1A);
    UiSetWidgetPos_290f60(o->m87C, 0xC361, 0, 0x1C);
    UiSetWidgetPos_290f60(o->m87C, 0xC362, 0, 0x1C);
    UiSetWidgetPos_290f60(o->m87C, 0xC363, 0x71, 0);
    UiSetWidgetPos_290f60(o->m87C, 0xC364, 0, 0x1C);
    UiSetWidgetPos_290f60(o->m87C, 0xC365, 0, 0x1C);
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC360, 0, insect_InsectPieceGetStat_512e20(r, 0, 0));
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC361, 0, insect_InsectPieceGetStat_512e20(r, 2, 0));
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC362, 0, insect_InsectPieceGetStat_512e20(r, 4, 0));
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC363, 0, insect_InsectPieceGetStat_512e20(r, 1, 0));
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC364, 0, insect_InsectPieceGetStat_512e20(r, 3, 0));
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC365, 0, insect_InsectPieceGetStat_512e20(r, 5, 0));

    for (i = 0; i < 6; i += 1) {
        w = ((Widget *)UiFindWidget_290460(o->m87C, insect_D_00524B80[i * 2]));
        if (w != 0) {
            a = w->m24;
            if (a != 0) {
                if (flag != 0) {
                    a->m12 = 0x3C;
                    a->m14 = 0;
                    a->m8 = 0;
                    a->m1A = a->m1A | 4;
                } else {
                    a->m12 = 0;
                    a->m14 = 0x12;
                    a->m1A = a->m1A & ~4;
                }
            }
        }
    }

    UiSetWidgetPos_290f60(o->m87C, 0xC366, 0, 0x76);
    UiSetWidgetPos_290f60(o->m87C, 0xC36B, 0, 0x1C);
    UiSetWidgetPos_290f60(o->m87C, 0xC36C, 0, 0x1C);
    UiSetWidgetPos_290f60(o->m87C, 0xC36A, 0x3C, 0);
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC36A, 0, r->m1A);
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC36A, 1, r->m1E);
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC36B, 0, r->m26);
    UiSetWidgetSubItemValue_291250(o->m87C, 0xC36C, 0, r->m28);

    for (i = 0; i < 3; i += 1) {
        w = ((Widget *)UiFindWidget_290460(o->m87C, insect_D_00524B98[i * 2]));
        if (w != 0) {
            a2 = w->m24;
            if (a2 != 0) {
                if (i == 0) {
                    for (j = 0; j < 2; j += 1) {
                        if (flag != 0) {
                            a2->m12 = 0x3C;
                            a2->m14 = 0;
                            a2->m8 = 0;
                            a2->m1A = a2->m1A | 4;
                        } else {
                            a2->m12 = 0;
                            a2->m14 = 0x12;
                            a2->m1A = a2->m1A & ~4;
                        }
                        a2 += 1;
                    }
                } else {
                    if (flag != 0) {
                        a2->m12 = 0x3C;
                        a2->m14 = 0;
                        a2->m8 = 0;
                        a2->m1A = a2->m1A | 4;
                    } else {
                        a2->m12 = 0;
                        a2->m14 = 0x12;
                        a2->m1A = a2->m1A & ~4;
                    }
                }
            }
        }
    }

    UiSpriteListFillColumnMaybe_3939e0(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC371)), 3, 1, 102.0f, 28.0f);
    UiSetWidgetPos_290f60(o->m87C, 0xC371, 4, 0xE);
    UiSetWidgetPos_290f60(o->m87C, 0xC369, 0x6A, 0);
    UiNineSliceLayoutMaybe_392440(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC36E)), 0x158, 0x68);
    UiSetWidgetPos_290f60(o->m87C, 0xC36E, 0, 0x50);
    UiSetTextStringPos_290b20(o->m87C, 0xC36E, r->m60, -1, -1, 0);
    w = ((Widget *)UiFindWidget_290460(o->m87C, 0xC36E));
    if (w != 0) {
        n = strlen(r->m60);
        b = w->m28;
        if (b != 0) {
            b->m0 = 6;
            b->m2 = 6;
            b->m10 = (s16)(n * 8 + 6);
            b->m12 = 6;
        }
    }
    UiSetTextStringPos_290b20(o->m87C, 0xC36F, r->m64, -1, -1, 0);
    UiSpriteListFillColumnMaybe_3939e0(g, ((Widget *)UiFindWidget_290460(o->m87C, 0xC370)), 1, 1, 328.0f, 0.0f);
    UiSetWidgetPos_290f60(o->m87C, 0xC370, 6, 0x18);

    if (o->m5DA8 != 0) {
        UiSetWidgetVisible_290010(o->m87C, 0xC35D, 0, -1);
        UiSetWidgetVisible_290010(o->m87C, id21, 0, -1);
        gl = ((Widget *)UiFindWidget_290460(o->m87C, 0xC358))->m20;
        gl->m2E = 0;
        gl->m2C = 0;
        gl->m26 = 0;
        gl->m24 = 0;
        UiSetWidgetAlpha_2907a0(o->m87C, 0xC35C, 0.5f);
        UiSetWidgetAlpha_2907a0(o->m87C, 0xC35A, 0.5f);
        UiSetWidgetAlpha_2907a0(o->m87C, 0xC358, 0.5f);
    }
    return 1;
}
