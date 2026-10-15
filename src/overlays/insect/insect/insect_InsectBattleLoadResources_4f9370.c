#include "types.h"
/* insect 0x004F9370 -- 1,424 bytes, 356 instructions, 60 calls, 19 conditional
 * branches, br/ins 0.053.  A thirteen-arm state dispatch on
 * insect_InsectBattleGetStep_50d6a0(o, 1), the insect_InsectBattleMenuTeamSelect_5004f0 family; read that unit's
 * prototype block first.
 *
 * It is a LOAD CHAIN: 0x3E through 0x45 and then 0x1D all FALL THROUGH, one
 * asset per state, each ending by pushing the next state with
 * insect_InsectBattleSetStep_50d7a0(o, <next>, 1, -1).  The tell that a state falls through
 * rather than breaking is that its block ends with that push and the NEXT
 * state's block label sits immediately after it, with no `b` to the exit.
 *
 * The compare chain runs 0xB, 0xA, 0x1D, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40,
 * 0x3F, 0x3E, 6, 1 -- REVERSED -- so the source case order is 1, 6, 0x3E,
 * 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x1D, 0xA, 0xB, which is the block
 * order forwards.
 *
 * `case 0xA: break;` IS IN THE SOURCE: its `beql` targets 0x004F98E8, one
 * instruction PAST the epilogue head 0x004F98E4 that every other exit branches
 * to, because the branch-likely already ran `ld $31, 0x40($29)` in its delay
 * slot.  Read the two exit addresses as DIFFERENT or the case disappears.
 *
 * D_00480F20 is MAIN-image small data (_gp is 0x00485170, the window is
 * 0x47D170..0x48D170) and is 6 bytes, at the small-data threshold, so it stays
 * NON-const to keep %gp_rel; the loop takes its ADDRESS and indexes, which is
 * why it reads `addiu $2, $28, -0x4250 / addu / lh` rather than a bare
 * gp-relative load.  D_005250xx and D_00525FF0 are OVERLAY data outside that
 * window -- the string tables are `const`, but D_00525FF0 is WRITTEN through
 * (`sw $2, 0x8($16)`) so it cannot be.
 *
 * DECLARATION ORDER IS LOAD-BEARING HERE AND THE SEARCH IS SMALL ENOUGH TO
 * ENUMERATE.  Four of the caller-saved values (`h`, `b`, `base`, `n`) plus the
 * loop counter `i` decide $16/$17/$18 in the 0x3E and 0x3F arms; the first
 * draft was 37 bad words, the 24 permutations of the four ran 13..26 and the
 * 120 with `i` added contained several exact hits.  `h, b, base, i, n` is one
 * of them.  LATER in the declaration list means a LOWER register here, which
 * is why `b` had to move after `h` and `i` after `base`.
 *
 * Three non-allocation levers were needed first:
 *   - a func_1C2800 result used as an argument BESIDE its own out-parameter
 *     must go through a TEMPORARY.  Written inline as
 *     `f(x, func_1C2800(..., &sp), sp)` mwcc evaluates `sp` before the call
 *     and folds it to the 0 it was just assigned -- `daddu $6, $0, $0` where
 *     retail reloads `lw $6, 0x60($29)`.  Three arms had this.
 *   - the 0x43 loop increments the COUNTER before the cursor, so the cursor
 *     step belongs in the `for` increment (`i += 1, q += 0x80`), not at the
 *     end of the body.
 *   - the eight frame slots are declared in DESCENDING address order
 *     (sp6C first, sp50 last).
 */

typedef struct Node {
    u8  pad00[0x8];
    s32 m8;                     /* +0x08 */
    u8  pad0C[0x14 - 0xC];      /* stride 0x14 */
} Node;

typedef struct Clip {
    u8    pad00[0x4];
    void *m4;                   /* +0x04 */
} Clip;

typedef struct Ent { u8 raw[0x58]; } Ent;

typedef struct Sb {
    u8    pad00[0x4];
    void *m4;                   /* +0x04 -- Ins+0x5B0C */
} Sb;

typedef struct Ins {
    u8   pad0000[0xC4];
    s32  mC4;                   /* +0x00C4 */
    s32  mC8;                   /* +0x00C8 */
    s32  mCC;                   /* +0x00CC */
    s32  mD0;                   /* +0x00D0 */
    u8   pad00D4[0xD8 - 0xD4];
    s32  mD8;                   /* +0x00D8 */
    u8   pad00DC[0xE0 - 0xDC];
    Ent  mE0[7];                /* +0x00E0 .. 0x0348 */
    Ent  m348;                  /* +0x0348 */
    Ent  m3A0;                  /* +0x03A0 */
    Ent  m3F8;                  /* +0x03F8 */
    u8   pad0450[0x5B0 - 0x450];
    u8   m5B0[0x710 - 0x5B0];   /* +0x05B0 */
    u8   m710[0x5000 - 0x710];  /* +0x0710 */
    u8   m5000[0x2C];           /* +0x5000 */
    u8   m502C[0x5058 - 0x502C];/* +0x502C */
    u8   m5058[0x506C - 0x5058];/* +0x5058 */
    u8   m506C[0x50E8 - 0x506C];/* +0x506C */
    u8   m50E8[0x5140 - 0x50E8];/* +0x50E8 */
    u8  *m5140;                 /* +0x5140 */
    u8   pad5144[0x5148 - 0x5144];
    s32  m5148;                 /* +0x5148 */
    u8   pad514C[0x5AF8 - 0x514C];
    u8   m5AF8[0x5B08 - 0x5AF8];/* +0x5AF8 */
    Sb   m5B08;                 /* +0x5B08 */
} Ins;

extern s16 D_00480F20[3];
extern const u8 D_00524CD8[];
extern const u8 D_00524CE8[];
extern const u8 D_00524CF8[];
extern const u8 D_00524D08[];
extern const u8 D_00524D18[];
extern const u8 D_00524D28[];
extern const u8 D_00524D40[];
extern const u8 D_00524D50[];
extern const u8 D_00524D60[];
extern const u8 D_00524D70[];
extern const u8 D_00524D88[];
extern const u8 D_00524DA0[];
extern Node D_00525FF0[];

extern void  func_14DAD0(void *b);
extern void  func_14DB10(void *b, s32 a, s32 c, s32 d);
extern s32   func_159FB0(s32 f, const u8 *name, s32 tag);
extern s32   func_15DE40(void);
extern s32   func_1C2800(s32 h, const u8 *name, s32 *sz);
extern s32   func_202A50(s32 h, const u8 *name, void *b);
extern void  func_202BE0(s32 h, const u8 *name, void *b, s32 tag, void *d);
extern s32   func_206A40(void);
extern void  func_2901D0(Node *n, void *p, s32 a, s32 b);
extern void  func_290390(Node *n, void *b, s16 v);
extern void  func_2912E0(Node *n);
extern void  func_391720(void *b, s32 p, s32 sz, s32 a);
extern void  func_42B840(s32 base, s32 a, s32 b, void *c, s32 h);
extern Clip *func_42C500(s32 base, s32 id);

extern void insect_InsectCmdMenuLoadLabels_4efb70(void *a, void *b);
extern void insect_InsectFormationParseScript_4efde0(void *a, s32 p, s32 sz);
extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32  insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern s32  insect_InsectFileSlotGetData_511fa0(void *a, s32 *out);
extern s32  insect_InsectFileSlotIsLoaded_512010(void *a);
extern void insect_InsectFileSlotRelease_512020(void *a);
extern void insect_InsectFileSlotRequest_512140(void *a, const u8 *t, s32 k);
extern s32  insect_InsectMsgGet_512b70(void *a, s32 k);
extern void insect_InsectMsgSetBank_512b80(void *a, s32 v);
extern void insect_InsectMsgClearBank_512b90(void *a);
extern void insect_InsectAbilityTableLoad_51d0b0(void *a, s32 p, s32 sz, s32 d);
extern void insect_InsectAbilitySetName_51d230(void *a, s32 v);
extern void insect_InsectAiCfgParseScript_522cc0(void *a, s32 p, s32 sz);
extern void insect_InsectAiCfgSetHeap_522e20(void *a, void *b);
extern void insect_InsectAiCfgInit_522e30(void *a);
extern void insect_InsectLiveTalkTableLoad_523540(Sb *a, s32 p, s32 sz);
extern void insect_InsectLiveTalkTableInit_5235c0(Sb *a);

void insect_InsectBattleLoadResources_4f9370(Ins *o)
{
    void *p;
    Clip *c;
    u8 *q;
    s32 f;
    s32 x;
    s32 cnt;
    s32 h;
    void *b;
    s32 base;
    s32 i;
    Node *n;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;

    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        insect_InsectFileSlotRequest_512140(o->m5000, D_00524CD8, 0);
        insect_InsectBattleSetStep_50d7a0(o, 6, 1, -1);
        break;
    case 6:
        if (insect_InsectFileSlotIsLoaded_512010(o->m5000) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x3E, 1, -1);
        }
        break;
    case 0x3E:
        sp6C = 0;
        h = insect_InsectFileSlotGetData_511fa0(o->m5000, &sp6C);
        b = o->mE0;
        func_14DB10(b, 2, 0, 0x40);
        func_202BE0(h, D_00524CE8, b, 0x29E, b);
        func_14DAD0(b);
        f = func_15DE40();
        o->mC4 = func_159FB0(f, D_00524CF8, 0x29E);
        o->mC8 = func_159FB0(f, D_00524D08, 0x29E);
        o->mCC = func_159FB0(f, D_00524D18, 0x29E);
        o->mD0 = func_159FB0(f, D_00524D28, 0x29E);
        insect_InsectBattleSetStep_50d7a0(o, 0x3F, 1, -1);
        /* fall through */
    case 0x3F:
        base = func_206A40();
        func_42B840(base, 2, 6, o->m3A0.raw,
                    insect_InsectFileSlotGetData_511fa0(o->m5000, &sp68));
        for (i = 0; i < 3; i += 1) {
            n = &D_00525FF0[i];
            if (n != 0) {
                func_2912E0(n);
                func_290390(n, o->mE0[i + 3].raw, D_00480F20[i]);
                c = func_42C500(base, i + 0x3E8);
                if (c != 0) {
                    func_2901D0(n, c->m4, 0, 0);
                    n->m8 = 0x29E;
                }
            }
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x40, 1, -1);
        /* fall through */
    case 0x40:
        p = o->m506C;
        insect_InsectMsgClearBank_512b90(p);
        sp64 = 0;
        h = insect_InsectFileSlotGetData_511fa0(o->m5000, &sp64);
        b = o->m348.raw;
        func_14DB10(b, 2, 0, 0x40);
        insect_InsectMsgSetBank_512b80(p, func_202A50(h, D_00524D40, b));
        func_14DAD0(b);
        insect_InsectCmdMenuLoadLabels_4efb70(o->m502C, p);
        insect_InsectBattleSetStep_50d7a0(o, 0x41, 1, -1);
        /* fall through */
    case 0x41:
        sp60 = 0;
        x = func_1C2800(insect_InsectFileSlotGetData_511fa0(o->m5000, &sp60), D_00524D50,
                        &sp60);
        insect_InsectFormationParseScript_4efde0(o->m5058, x, sp60);
        insect_InsectBattleSetStep_50d7a0(o, 0x42, 1, -1);
        /* fall through */
    case 0x42:
        sp5C = 0;
        x = func_1C2800(insect_InsectFileSlotGetData_511fa0(o->m5000, &sp5C), D_00524D60,
                        &sp5C);
        func_391720(o->m3F8.raw, x, sp5C, 0);
        insect_InsectBattleSetStep_50d7a0(o, 0x43, 1, -1);
        /* fall through */
    case 0x43:
        sp58 = 0;
        x = func_1C2800(insect_InsectFileSlotGetData_511fa0(o->m5000, &sp58), D_00524D70,
                        &sp58);
        insect_InsectAbilityTableLoad_51d0b0(o->m50E8, x, sp58, o->mD8);
        insect_InsectBattleSetStep_50d7a0(o, 0x44, 1, -1);
        cnt = o->m5148;
        q = o->m5140;
        for (i = 0; i < cnt; i += 1, q += 0x80) {
            insect_InsectAbilitySetName_51d230(q, insect_InsectMsgGet_512b70(o->m506C, i + 0x384));
        }
        /* fall through */
    case 0x44:
        sp54 = 0;
        x = func_1C2800(insect_InsectFileSlotGetData_511fa0(o->m5000, &sp54), D_00524D88,
                        &sp54);
        insect_InsectAiCfgInit_522e30(o->m5AF8);
        insect_InsectAiCfgSetHeap_522e20(o->m5AF8, o->m5B0);
        insect_InsectAiCfgParseScript_522cc0(o->m5AF8, x, sp54);
        insect_InsectBattleSetStep_50d7a0(o, 0x45, 1, -1);
        /* fall through */
    case 0x45:
        sp50 = 0;
        x = func_1C2800(insect_InsectFileSlotGetData_511fa0(o->m5000, &sp50), D_00524DA0,
                        &sp50);
        insect_InsectLiveTalkTableInit_5235c0(&o->m5B08);
        o->m5B08.m4 = o->m710;
        insect_InsectLiveTalkTableLoad_523540(&o->m5B08, x, sp50);
        insect_InsectBattleSetStep_50d7a0(o, 0x1D, 1, -1);
        /* fall through */
    case 0x1D:
        insect_InsectFileSlotRelease_512020(o->m5000);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
        break;
    case 0xA:
        break;
    case 0xB:
        if (insect_InsectBattleTestFlag_50da40(o, 5) != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        }
        break;
    }
}
