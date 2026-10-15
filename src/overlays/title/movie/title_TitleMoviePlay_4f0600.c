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
 * D_004F1628 is overlay data at 0x4F1628, 0x6C4B8 past _gp, so it must be
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
extern const u8 D_004F1628;

extern void func_15DC40(void);
extern void func_17FE80(s32 a);
extern Scn_title_FUN_004f0600 *func_1C6C70(void);
extern Wk_title_FUN_004f0600 *func_15DE80(void);
extern void *func_15DE40(void);
extern void *func_1451E0(Wk_title_FUN_004f0600 *a);
extern void func_1451D0(Wk_title_FUN_004f0600 *a);
extern void *func_145140(Wk_title_FUN_004f0600 *a);
extern void *func_14E230(s32 a, void *b);
extern Big_title_FUN_004f0600 *func_1D6130(void *a);
extern void func_14D8E0(void *a);
extern void func_1D6230(View_title_FUN_004f0600 *a);
extern void func_1D61C0(View_title_FUN_004f0600 *a, void *b, void *c);
extern void func_1D61A0(Big_title_FUN_004f0600 *a, View_title_FUN_004f0600 *b);
extern void func_1D52E0(Big_title_FUN_004f0600 *a, f32 b);
extern void func_158AC0(void *a, s32 b);
extern void func_159B70(void *a, s32 b, const u8 *c, s32 d, void *e, s32 f,
                        void *g, s32 h, s32 i, s32 j);
extern void func_158AB0(void *a, s32 b);
extern void func_1D5B50(Big_title_FUN_004f0600 *a, const u8 *b);
extern void func_1D5810(Big_title_FUN_004f0600 *a);
extern s32 func_1D5640(Big_title_FUN_004f0600 *a);

s32 title_TitleMoviePlay_4f0600(void *a, void *b, s32 c, s32 d)
{
    View_title_FUN_004f0600 sp;
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

    func_15DC40();
    D_00480430 = -1;
    D_0048429C = b;
    func_17FE80(0);
    scn = func_1C6C70();
    wk = func_15DE80();
    drv = func_15DE40();
    ta = func_1451E0(wk);
    func_1451D0(wk);
    tb = func_145140(wk);
    wk->field3D2C = 0;
    arc = func_14E230(0x17980, b);
    if (arc != 0) {
        arc = func_1D6130(arc);
    }
    D_00484290 = arc;
    func_14D8E0(b);
    func_1D6230(&sp);
    func_1D6230(&sp);
    func_1D61C0(&sp, a, b);
    sp.field0E0 = (c != 0);
    sp.field0D8 = 0x200;
    sp.field0DC = 0x1C0;
    func_1D61A0(D_00484290, &sp);
    big = D_00484290;
    big->field17970 = 0;
    big->field17974 = 0;
    func_1D52E0(D_00484290, 1.0f);
    n = scn->field5CF4;
    m = scn->field5CF0;
    slot = n;
    D_004842A0 = m;
    if (n <= 0) {
        return 0;
    }
    func_158AC0(drv, 0x32C);
    func_158AC0(drv, D_004842A0);
    func_159B70(drv, D_004842A0, &D_004F1628, 0, ta, 0x1C0, tb, 0, 0, 0);
    func_158AB0(drv, D_004842A0);
    func_1D5B50(D_00484290, &D_004F1628);
    func_1D5810(D_00484290);
    while ((idle = !(func_1D5640(D_00484290) != 0)) != 0) {
        func_1D5810(D_00484290);
    }
    func_1D5810(D_00484290);
    D_00480430 = d;
    D_00484288 = 0;
    return 1;
}
