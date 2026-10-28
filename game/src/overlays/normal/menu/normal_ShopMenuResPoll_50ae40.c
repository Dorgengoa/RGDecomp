/* rgp:protos */
#define RGP_SELF_normal_ShopMenuResPoll_50ae40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050AE40 -- drafted s26.  Walks the two-entry gp table at
 * `gp - 0x4B30`, (re)builds whichever slot is not yet live, tears the slot's
 * old handle down, then sums the two slots' f04 and reports whether BOTH came
 * up.  Two calls take FIVE arguments ($8), so the callee prototypes are wide.
 *
 * Read off the listing, used as drafting constraints rather than repairs:
 *   * `sw $2, 0x0($16)` sits in the DELAY SLOT of a PLAIN `bne`, so the store
 *     of func_1CD4F0's result into `s->f04` is UNCONDITIONAL and the test reads
 *     the stored field -- not `if (f(..) == 1) { s->f04 = ..; }`.
 *   * `bnel $18, $0` guards the i==0 arm even though the loop only runs i=0,1,
 *     so the source spells a redundant `else if (i == 0)`, not a bare `else`.
 *   * the tail's `sh $2, -0xB8C($28)` rides the `b` delay slot with $2 already
 *     holding the returned 1, so the store and the `return 1` share the value.
 *
 * BYTE-IDENTICAL, s26.  Four levers, in the order they paid:
 * 1. ****** THE SMALL-DATA SIZE THRESHOLD FIRES IN BOTH DIRECTIONS IN ONE UNIT.
 *    `D_00480640` is reached gp-relative by retail (`addiu $2,$28,-0x4B30`,
 *    ONE word) but a `[2]` declaration is 16 B, over the threshold, and got a
 *    two-word `lui %hi / addiu %lo`.  `normal_D_00526500`/`normal_D_00526510` are the mirror:
 *    declared `const void *` they are 4 B, UNDER the threshold, and went
 *    gp-relative where retail has `lui %hi / addiu %lo`.  Declaring the table
 *    `[1]` and the descriptors `const u8 [0x10]` fixed both at once and closed
 *    three hunks.  [[im-gp-array-sdata-threshold]] -- and the lesson is to
 *    check the direction PER SYMBOL, because a unit can be wrong both ways.
 * 2. `s = &D_00480640[(u32)i]` -- retail RECOMPUTES the slot address after the
 *    if/else (`sll/addiu/addu` at 0x0050AF6C) and mwcc had CSE'd our second
 *    `&D_00480640[i]` with the first.  [[mwcc-index-cast-defeats-cse]], the
 *    direction where the cast BUILDS the recompute.  +1 word.
 * 3. The tail: ONE trailing `return 0` reached by both edges, not a `return 0`
 *    inside the `total == 2` arm as well.  Right length at 9 bad from 3 short.
 *    [[mwcc-mixed-exit-statements]] -- and note the 2^2 lattice's other three
 *    cells (inner goto, inner else, named result) are all still length-wrong.
 * 4. ★★★★★★ THE CLOSER: store through `&s->f04`, not through `s->f04`.
 *    `pf = &s->f04; *pf = func_1CD4F0(...); if (*pf == 1)` took 9 bad -> 0.
 *    Retail materialises `addiu $16,$17,4` in the FIRST branch's DELAY SLOT and
 *    stores `sw $2, 0x0($16)`; through the member it is `sw $2, 0x4($16)` and
 *    the slot has to take `i++` instead, which flips BOTH branches' likely/plain
 *    shapes as well.  [[mwcc-member-address-no-cse]]: the &member AT THE STORE
 *    SITE decides what the scheduler can sink.  One edit, 9 words, three
 *    apparently independent residues (a register, a store displacement and two
 *    branch-likely shapes) -- they were ONE defect.
 *    ⚠ The DECLARATION POSITION of `pf` is inert (2 arms, one object 34899f30).
 */

typedef struct Slot { s32 f00; s32 f04; } Slot;

extern Slot D_00480640[1];        /* gp - 0x4B30, declared SHORT: retail
                                   * reaches it gp-relative, so the declared
                                   * size must stay under the sdata threshold */
extern void *D_004845AC;          /* gp - 0xBC4 */
extern void *D_004845F8;          /* gp - 0xB78 */
extern s8    D_004845DC;          /* gp - 0xB94 */
extern void *D_004845FC;          /* gp - 0xB74 */
extern s16   D_004845E4;          /* gp - 0xB8C */
extern u8 normal_D_00526500[0x10];
extern u8 normal_D_00526510[0x10];

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

s32 normal_ShopMenuResPoll_50ae40(void)
{
    s32 sp7C;
    void *r;
    void *w;
    s32 total;
    s32 i;
    void *obj;
    void *g;
    Slot *s;
    s32 *pf;
    s32 j;

    w = GetLoaderMgr_1f59d0();
    total = 0;
    i = 0;
    do {
        s = &D_00480640[i];
        pf = &s->f04;
        if (s->f04 == 0) {
            if (s->f00 != -1) {
                *pf = LoaderGetStatus_1cd4f0(w, s->f00);
                if (*pf == 1) {
                    obj = LoaderGetData_1cd490(w, s->f00, &sp7C);
                    g = D_004845AC;
                    if (i == 1) {
                        ResGroupLoadByKind_42b840(GetMenuResGroup_206a40(), 2, 3, g, obj);
                        D_004845F8 = MsgTableLoadFromArchive_202a50(obj, normal_D_00526500, g);
                        TexGroupLoadFromArchive_202be0(obj, normal_D_00526510, g, 0x32D, 0);
                        D_004845DC = 1;
                    } else if (i == 0) {
                        r = GetDrawCtxNameTable_15de40();
                        MemMoveIfDiff_289c60(obj, sp7C, D_004845FC);
                        NameTableRegisterImArchive_1594d0(r, D_004845FC, 0x32E, g, 0);
                    }
                    s = &D_00480640[(u32)i];
                    LoaderReleaseById_1cd340(w, s->f00);
                    s->f00 = -1;
                    normal_ShopMenuIconClutBuild_50b110();
                }
            }
        }
        i++;
    } while (i < 2);

    for (j = 0; j < 2; j++) {
        total += D_00480640[j].f04;
    }

    if (total == 2) {
        if (WorldDataMgrNoRequestPending_3eef10(GetWorldDataMgr_1fedf0()) != 0) {
            D_004845E4 = 1;
            return 1;
        }
    }
    return 0;
}
