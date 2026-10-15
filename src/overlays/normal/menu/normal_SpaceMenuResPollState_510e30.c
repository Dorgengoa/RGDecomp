/* SESSION 39 (n39b, SOLO): 2 bad -> MATCH, 66/66 words, byte-identical.
 * Identical defect and identical fix to this unit's latch-pair sibling
 * normal_InsectEntryMenuResPoll_524680 (closed the same session): func_1CD4F0 takes TWO
 * arguments, (void *h, s32 id), in all 8 merged declarations of it in the
 * corpus; this file declared it with one.  Writing
 *     D_00480674 = func_1CD4F0(h, D_00480670) != 0;
 * turns retail's `lw $5,-0x4B00($28)` at 0x00510E50 into what it is -- the
 * second ARGUMENT setup, hoisted into a branch-likely delay slot -- and the
 * `D_00480670 <= -1` guard's `slti $1,$5,0` at 0x00510E5C then reuses that
 * argument register instead of a private v0 guard temp.  Both bad words in
 * one edit.  See [[merged-callee-signature-oracle]]. */
/* SESSION 35 (n35e, 2026-09-06): superseded the s29 note below. Starting
 * point was 17 bad (the s29 `#pragma opt_repositioncode on` state). That
 * pragma is INCOMPATIBLE with matching retail's guard shapes here -- it was
 * REMOVED. Two source-level levers instead get this to 66/66 words, 2 bad:
 *   1. EXIT SINK: the `D_00480674 != 1` guard's `return 0;` is sunk to
 *      `goto tail;` sharing the function's trailing `return 0;` -- this is
 *      what makes mwcc emit one clean `bnel` there instead of a 3-word
 *      beql/lw/beq detour, and also fixes the OTHER two guards' shapes as a
 *      side effect (all three now match retail exactly in construction).
 *   2. `D_00480670 < 0` spelled as `D_00480670 <= -1` (identical semantics)
 *      -- defeats mwcc's peephole fold of `slti+beql` into a 1-word
 *      `bgezl`, which is what retail's length actually needs (2 words).
 * REMAINING 2-WORD RESIDUE (0x00510E50 `lw`, 0x00510E5C `slti`): pure
 * REGISTER CHOICE. Retail puts the freshly-loaded D_00480670 value in `a1`;
 * every build here puts it in `v0`. Tried and CONFIRMED INERT: named locals
 * at 3 different lifetimes/positions, a volatile pin, `!(x>=0)` /
 * `(s32)x<0` / `0>x` spellings, declaration-order swaps (h/q, id-first), and
 * `#pragma opt_common_subs`, `peephole`, `no_branch_likely`,
 * `opt_foldconstants`, `opt_dead_assignments`, `scheduling`,
 * `opt_constnonchanging` all off/on scoped every way tried. This looks like
 * an mwcc allocator-internal counter artifact, not a reachable C/pragma
 * lever from this corpus's known list -- next session should try the
 * `mwcc -g` DWARF register-oracle lever on a probe build if available.
 * SESSION n38f (2026-09-06): re-confirmed the volatile-pin null on the
 * `D_00480670` read itself (`*(volatile s32*)&D_00480670 <= -1`) -- same
 * object, still 2 bad. No new arm found; parked as-is, not attempted
 * further this session (round-trip cap). */
#include "types.h"
/* normal 0x00510E30 -- one-shot loader: the u8 latch at 0x00480674 and the
 * handle at 0x00480670 gate everything, then the pack is opened, two records
 * pulled out of it and the handle released. */
extern u8    D_00480674;          /* gp - 0x4AFC */
extern s32   D_00480670;          /* gp - 0x4B00 */
extern void *D_004846B0;          /* gp - 0xAC0  */
extern void *D_004846AC;          /* gp - 0xAC4  */
extern void *D_004846B4;          /* gp - 0xABC  */
extern u8    D_00526560[];
extern u8    D_00526570[];

extern void *func_1F59D0(void);
extern s32   func_1CD4F0(void *h, s32 id);
extern void  func_14D8E0(void *p);
extern void *func_1CD490(void *h, s32 id, s32 *out);
extern void *func_206A40(void);
extern void  func_42B840(void *a, s32 b, s32 c, void *d, void *e);
extern void *func_202A50(void *a, u8 *b, void *c);
extern void  func_202BE0(void *a, u8 *b, void *c, s32 d, s32 e);
extern void  func_1CD340(void *h, s32 id);
extern void  func_28EDE0(void *p, s32 a, s32 b);

s32 normal_SpaceMenuResPollState_510e30(void)
{
    void *h;
    void *q;
    s32   tmp;

    h = func_1F59D0();
    if (D_00480674 != 0) {
        return 1;
    }
    if (D_00480670 <= -1) {
        return 1;
    }
    D_00480674 = func_1CD4F0(h, D_00480670) != 0;
    if (D_00480674 != 1) {
        goto tail;
    }
    func_14D8E0(D_004846B0);
    q = func_1CD490(h, D_00480670, &tmp);
    func_42B840(func_206A40(), 2, 0xA, D_004846B0, q);
    D_004846AC = func_202A50(q, D_00526560, D_004846B0);
    func_202BE0(q, D_00526570, D_004846B0, 0x32D, 0);
    func_1CD340(h, D_00480670);
    D_00480670 = -1;
    func_28EDE0(D_004846B4, 4, 1);
tail:
    return 0;
}
