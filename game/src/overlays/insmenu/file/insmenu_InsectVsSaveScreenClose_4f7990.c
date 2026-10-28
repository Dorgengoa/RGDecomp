/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveScreenClose_4f7990 1
#include "port/game_protos.h"
#line 1
/* insmenu 0x004F7990 (528 bytes, 132 instructions) -- BYTE-IDENTICAL.
 * Closed 2026-08-27, lane im37.  Was PARKED at 13 bad words (right length,
 * wrong bytes) after 330 source spellings and 1,523 knob arms in lane C3.
 *
 * ===================== WHAT THE RESIDUE ACTUALLY WAS ====================
 * Two disjoint REGISTER-PAIR swaps with no instruction differences at all.
 * All three levers below are REGISTER-ALLOCATION levers; not one of them
 * changes an opcode, an operand role or a slot.  In the order they paid:
 *
 *  1. `Ent.f0` is UNSIGNED (u32), the sentinel is 0xFFFFFFFF and the compare
 *     is `(u32)kind == tbl[i].f0`.  Worth 4 words: it closes the $3<->$6 swap
 *     inside the search loop's sign-extension chain.  Every SIGNED spelling
 *     of that loop is one of two dozen measured negatives.
 *
 *  2. `i++`, NOT `i = i + 1`.  With `i = i + 1` mwcc gives the loop ENTRY
 *     value its own register ($3) instead of the loop-carried one; with `i++`
 *     (and `i += 1` -- same object) the entry value lands in the register
 *     `dst` has just vacated, which is what retail does.  Compound assignment
 *     again, cf. [[insect-compound-assign-blocks-fold]].
 *
 *  3. ** `kind` IS DECLARED FIRST OF THE FOUR LOOP LOCALS. **  This is the
 *     whole 7-word residue and the reason twelve earlier vsweep rounds could
 *     not find it: lane C3 swept every position of `src` CROSSED with every
 *     position of `kind` (89 arms) but never moved `dst`, and with `dst`
 *     pinned the trio {src,dst,n} and the outsider `kind` cannot exchange
 *     register classes.  The rule, measured over all 24 permutations twice:
 *     the four locals are handed $8,$7,$6,$5 IN DECLARATION ORDER, so
 *     `kind, src, dst, n` puts kind in $8 (retail spills kind out of the
 *     argument-class run) and src/dst/n in $7/$6/$5.  Declaring `src` first
 *     -- the spelling this file carried for twelve rounds -- puts src in $8
 *     and kind in $7, which is exactly the seven-word swap.
 *
 * ========================= MEASURED NEGATIVES ==========================
 * All scored with build/im37_score.py, which diffs a mini-repro object
 * against asm/.../insmenu_InsectVsSaveScreenClose_4f7990.s word for word (masking relocated
 * fields) and agrees with dv_osbuild exactly -- 13 on the old source, 0 here.
 *   * COMPILER KNOBS re-run PROPERLY ANCHORED: 486 arms, both polarities,
 *     471 INERT / 15 live, floor unmoved.  (The first attempt inserted the
 *     pragma into this comment block and read 486/486 INERT -- that uniform
 *     result was the broken-filter tell.  Arming control: `#pragma
 *     opt_dead_assignments on` must give 131 words.)
 *   * valued pragmas optimization_level / opt_level 0-4, inline_depth 0-5,
 *     inline_max_size, scheduling, opt_unroll_count: all LEN or inert.
 *   * declaration LAYOUT of the other five locals (hnd/ctx/fl/code/i), 12
 *     layouts x 2 increment spellings: kind's register never moves.
 *   * inlined static helpers for the search, for the copy, and for the
 *     compare with `kind` passed VERBATIM as an argument: all wrong length.
 *   * LICM (comparing ctx->field1188->field08 directly), the kp split across
 *     the copy loop, kind assigned twice: 131 / 21 / 22 words respectively.
 *   * `#pragma opt_dead_assignments off` is still LOAD-BEARING -- without it
 *     the unit is 131 words (the frame-displacement addiu folds away).
 */
#pragma opt_dead_assignments off
#include "types.h"

/* insmenu 0x004F7990 (528 bytes, 132 instructions, 18 calls) -- close the
 * menu and hand the chosen code back.  ⚠ The flag is `$5`, the SECOND
 * parameter; the first is never read.
 *
 * The 18-entry table is COPIED onto the frame a field at a time (two `lw`/`sw`
 * pairs per iteration), then searched; `func_430B70` is called with no
 * argument set up at all because `$4` still holds the context loaded before
 * both loops.
 *
 * NO LONGER PARKED -- byte-identical as of 2026-08-27 (lane im37); see the
 * file-head block for the three levers.  NOT yet in config/ocunits/insmenu.txt:
 * merging is the board owner's call, not this lane's.
 *
 * SUPERSEDED: the paragraphs this block used to carry (the latch, the
 * bnel-with-a-duplicated-lw, and the 33 spellings behind them) described a
 * defect lane C3 (im13) FIXED; the 13-word register residue that replaced it
 * is now closed too.  Both are RETRACTED, not merely stale.
 */

typedef struct Ent Ent;
struct Ent {
    u32 f0;
    s32 f4;
};

typedef struct Flags Flags;
struct Flags {
    u8 pad00[4];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 rest : 5;
};

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s32 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad0000[0x1188];
    Kind *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    Ctx *field24;
};

extern u8 insmenu_D_004FA180[];
extern Ent insmenu_D_004F98A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];
extern f32 D_0047D3C8;      /* gp - 0x7DA8 */

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

s32 insmenu_InsectVsSaveScreenClose_4f7990(s32 p1, s32 open)
{
    Ent tbl[0x12] __attribute__((aligned(16)));
    Handle *hnd;
    Ctx *ctx;
    Flags *fl;
    s32 kind;
    const Ent *src;
    Ent *dst;
    s32 n;
    s32 code;
    s16 i;

    if (open != 0) {
        insmenu_InsectVsSetSceneBgFlagMaybe_4f3310(1);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88B9, 0.0f, D_0047D3C8, -1.0f);
        insmenu_InsectVsTitleBannerLayout_4ea600();
        SaveMgrRelease_37bb70();
        insmenu_InsectVsSceneRenderRestore_4e9f40();
    }
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x88B9) <= 0.0f) {
        hnd = ((Handle *)GetGameData_1fede0());
        ctx = hnd->field24;
        src = insmenu_D_004F98A0;
        code = 0x12D;
        dst = tbl;
        n = 0x12;
        kind = ctx->field1188->field08;
        do {
            n -= 1;
            dst->f0 = src->f0;
            dst->f4 = src->f4;
            src += 1;
            dst += 1;
        } while (n > 0);
        i = 0;
        while (tbl[i].f0 != 0xFFFFFFFF) {
            if ((u32)kind == tbl[i].f0) {
                code = tbl[i].f4;
                break;
            }
            i++;
        }
        if (code == -100) {
            fl = ((Flags *)RecordGetPayloadIfKind1E_430b70(ctx));
            if (fl != 0) {
                if (fl->b1) {
                    code = 0x12D;
                }
            }
        } else if (code == -200) {
            fl = ((Flags *)RecordGetPayloadIfKind1E_430b70(ctx));
            if (fl != 0) {
                if (fl->b2) {
                    code = 0x12D;
                }
            }
        }
        RecordSetStateClamped_430db0(hnd->field24, code, 0);
        insmenu_InsectVsMenuEnterRecordStep_4f1b10();
        insmenu_InsectVsTasksResume_4e9f00();
        PadClearRepeatAll_183960(D_004B2570);
        PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
        PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
        PadClearRepeatAll_183960(D_004B27E0);
        PadSetRepeat_183d50(D_004B27E0, 0xF00C, 0xA, 3);
        PadSetStickDpadThreshold_183950(D_004B27E0, 0x78);
    }
    return 1;
}
