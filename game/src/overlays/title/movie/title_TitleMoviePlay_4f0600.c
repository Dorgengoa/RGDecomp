/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_title_TitleMoviePlay_4f0600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F0600 -- brings up the title scene: reset the state
 * word, build the scene objects, load and configure the 0x17980 archive, then
 * spin a present loop until func_1D5640 reports ready.
 *
 * THE VIEW STRUCT IS 0xEC BYTES AND `0x18C($29)` IS NOT ONE OF ITS MEMBERS.
 * Sessions 1-12 read the frame as a 0xF0-byte `sp` at 0xA0($29) whose last
 * word is 0x18C, and wrote `sp.field0EC = n;`.  That spelling is 2 words wrong
 * and no spelling, declaration order, pragma or compiler build reaches retail
 * from it.  0xA0 + 0xEC = 0x18C is equally consistent with `sp` ENDING at
 * 0x18C and a SEPARATE 4-byte local sitting above it in a 0x190 frame, and
 * that is what it is: the slot is written once and never read back, so nothing
 * in the listing distinguishes the two readings.  The main-image twin of this
 * routine, MoviePlayModal_267c60, has the identical pair -- view at 0x170($29), the
 * slot at 0x25C($29) = view+0xEC, frame 0x260 -- so the layout is forced by
 * alignment, not a coincidence.
 *
 * THE LEVER IS `volatile` ON A STANDALONE LOCAL, AND IT IS NOT ABOUT ALIASING.
 * A plain `s32 slot;` written and never read is dead-store-eliminated (135
 * words, one SHORT -- that is this axis's arming proof).  `volatile` pins the
 * store, mwcc issues it before the gp store to D_004842A0, and the gp store
 * takes the branch delay slot, which is retail.  Measured on a 12-word
 * mini-repro (src/overlays/title/timini.c) and confirmed on the whole function:
 *   - volatile standalone local, declared first / after sp / last:  ALL EXACT
 *   - `volatile` on the STRUCT MEMBER field0EC instead:             2 bad, inert
 *   - non-volatile standalone local, address taken by a later call: 2 bad
 *   - non-volatile standalone local, address taken before the store:2 bad
 *   - a separate 4-byte address-taken STRUCT in the slot:           2 bad
 * so escape analysis does not reach this and the volatile qualifier does.  The
 * pin is positional, not order-preserving: writing the gp store FIRST in source
 * still emits the volatile store first.
 *
 * title_D_004F1628 is overlay data at 0x4F1628, 0x6C4B8 past _gp, so it must be
 * `const` -- %gp_rel would compile clean and die at link time.
 *
 * The present loop's condition is MATERIALISED: retail is
 * `sltu $2,$0,$2 / xori $2,$2,1 / bnez $2`, not a bare `beqz`, which is the
 * recorded "a bool built from an inequality and negated in one expression"
 * shape.  `while (!(f(p) != 0))` folds to `beqz` and is TWO WORDS SHORT; the
 * assignment-inside-the-test form is exact.  NOTE it must be `s32`: a `u8`
 * `idle` is the right length and wrong in the loop's two words.
 */

typedef struct View_title_FUN_004f0600 {
    u8 pad000[0xD8];
    s32 field0D8;
    s32 field0DC;
    u8 field0E0;
    u8 pad0E1[0xB];
} View_title_FUN_004f0600;

typedef struct Scn_title_FUN_004f0600 {
    u8 pad0000[0x5CF0];
    s32 field5CF0;
    s32 field5CF4;
} Scn_title_FUN_004f0600;

typedef struct Wk_title_FUN_004f0600 {
    u8 pad0000[0x3D2C];
    s32 field3D2C;
} Wk_title_FUN_004f0600;

typedef struct Big_title_FUN_004f0600 {
    u8 pad00000[0x17970];
    s32 field17970;
    s32 field17974;
} Big_title_FUN_004f0600;

extern s32 D_00480430;
extern void *D_0048429C;
extern Big_title_FUN_004f0600 *D_00484290;
extern s32 D_004842A0;
extern s32 D_00484288;
extern u8 title_D_004F1628;

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

s32 title_TitleMoviePlay_4f0600(void *a, void *b, s32 c, s32 d)
{
    View_title_FUN_004f0600 sp __attribute__((aligned(16)));
    volatile s32 slot;
    Scn_title_FUN_004f0600 *scn;
    Wk_title_FUN_004f0600 *wk;
    void *drv;
    void *ta;
    void *tb;
    void *arc;
    Big_title_FUN_004f0600 *big;
    s32 n;
    s32 m;
    s32 idle;

    DrawCtxVif1HandlerStop_15dc40();
    D_00480430 = -1;
    D_0048429C = b;
    CdDiskWatchSetEnabled_17fe80(0);
    scn = ((Scn_title_FUN_004f0600 *)GetStaticScene_1c6c70());
    wk = ((Wk_title_FUN_004f0600 *)GetDrawCtx_15de80());
    drv = GetDrawCtxNameTable_15de40();
    ta = DrawEnvGetWidth_1451e0(wk);
    DrawEnvGetHeight_1451d0(wk);
    tb = DrawEnvGetPsmBpp_145140(wk);
    wk->field3D2C = 0;
    arc = MemStackNew_14e230(0x17980, b);
    if (arc != 0) {
        arc = ((Big_title_FUN_004f0600 *)MoviePlayerCtor_1d6130(arc));
    }
    D_00484290 = arc;
    MemStackAlign64_14d8e0(b);
    MovieOpenParamInit_1d6230(&sp);
    MovieOpenParamInit_1d6230(&sp);
    MovieOpenParamSetSource_1d61c0(&sp, a, b);
    sp.field0E0 = (c != 0);
    sp.field0D8 = 0x200;
    sp.field0DC = 0x1C0;
    MoviePlayerOpen_1d61a0(D_00484290, &sp);
    big = D_00484290;
    big->field17970 = 0;
    big->field17974 = 0;
    AudioDecSetInputVolumeF_1d52e0(1.0f);
    n = scn->field5CF4;
    m = scn->field5CF0;
    slot = n;
    D_004842A0 = m;
    if (n <= 0) {
        return 0;
    }
    NameTableFreeGroup_158ac0(drv, 0x32C);
    NameTableFreeGroup_158ac0(drv, D_004842A0);
    NameTableAddEntry_159b70(drv, D_004842A0, &title_D_004F1628, 0, ta, 0x1C0, tb, 0, (long long)(0), 0);
    TexGroupAllocVramDefault_158ab0(drv, D_004842A0);
    MoviePlayerStart_1d5b50(D_00484290, &title_D_004F1628);
    MoviePlayerWaitTick_1d5810(D_00484290);
    while (((idle = !(((unsigned char)MovieIsStarted_1d5640()) != 0)) != 0) && (rg_spin_hint(0x104F07BC), 1)) {
        MoviePlayerWaitTick_1d5810(D_00484290);
    }
    MoviePlayerWaitTick_1d5810(D_00484290);
    D_00480430 = d;
    D_00484288 = 0;
    return 1;
}
