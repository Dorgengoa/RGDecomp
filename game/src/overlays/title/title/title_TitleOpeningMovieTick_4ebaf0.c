/* rgp:protos */
#define RGP_SELF_title_TitleOpeningMovieTick_4ebaf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EBAF0 -- the attract-loop driver.  An idle timer that
 * arms a prompt, a five-way pad poll, and a fade counter that either restarts
 * the demo or steps the attract sequence.
 *
 * The five `func_1839F0` polls all branch to the SAME block, and the three
 * checks after it all branch to the same skip -- an `||` chain feeding an `&&`
 * chain, which is why only the first poll's delay slot carries the shared
 * `lh` and the other four fall into it.
 *
 * PARKED at 14 words in two clusters, both the same register-pressure shape:
 * retail computes a guard into **$at** where we get an ordinary register, which
 * by the existing rule means retail had one more value simultaneously live.
 *  - the D_00484164 pair: retail `slti $1, $3, 6` in the `bnel` delay slot,
 *    ours `slti $2` -- retail treats the branch's own source register as live
 *    through the slot and we reuse it.  `&&` and the nested form give the
 *    identical object.
 *  - the tail counter: retail leaves `sh $2, D_00484198` for a PLAIN `bnez`
 *    delay slot, which keeps $2 live and forces $at; we schedule the store
 *    early, $2 dies, and the branch becomes `bnezl` carrying the next guard's
 *    constant.  `volatile` on the counter costs a word instead of saving one,
 *    and dropping the s16 local to increment the global in place gives a
 *    BYTE-FOR-BYTE IDENTICAL object.
 *
 * ★ THE $at IS A CONSEQUENCE, NOT THE DEFECT.  title_FUN_004EDEC0 MATCHES and
 * contains `slti $1, $2, 0x3`, so this toolchain does emit $at -- it is source
 * driven, not a build difference.  In the tail cluster retail has BOTH $2 (the
 * sum, waiting for the delay-slot store) and $3 (the sign-extended value, read
 * again by the ==0xC test) live at the compare, so the compare needs a third
 * register and takes $at.  We schedule the store early, $2 dies, and the
 * compare takes $2 -- which then leaves nothing for the delay slot and the
 * branch degrades to the likely form.  ⇒ THE TARGET IS THE STORE'S POSITION,
 * and the register and the branch kind both follow from it.
 *
 * ⚠⚠ THIS IS THE HIGHEST-VALUE OPEN RESIDUE IN THE OVERLAY.  Both clusters
 * recur verbatim in title_FUN_004EAB10 and title_FUN_004EAD40 -- which are the
 * same function as each other in 139 of 140 words, differing only in one
 * immediate (`slti $2,$3,0x3C6E` against `0x112E`).  One fix would land about
 * 1,680 bytes, 5.7% of the overlay, so it is worth more than another small
 * unit.  It is an ALLOCATION residue, not a spelling: mwcc-ours will write the
 * branch's own source register in that branch's delay slot and retail's will
 * not, which means retail had one more value simultaneously live at both
 * points and the pressure comes from somewhere this reading has not found.
 */

extern s16 D_0048416C;
extern s32 D_00484164;
extern s16 D_00481B90;
extern s16 D_00484194;
extern s16 D_00484198;
extern void *D_00484154;
extern void *D_00484158;
extern void *D_00484160;
extern void *D_00484170;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;
extern f32 D_004803B0;
extern f32 D_004803B4;
extern void *D_004803D4;
extern f32 D_0047D56C;
extern u8 D_004B2570;
extern void *const title_D_004F1404;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleOpeningMovieTick_4ebaf0(s32 a)
{
    s32 m;
    s16 n;

    if (a != 0) {
        D_0048416C = 0;
        D_00484164 = 0;
    }
    if (D_00484164 >= 0x168) {
        D_0048416C = 0;
    } else if (D_00484164 > 5 && D_0048416C == 0) {
        D_0048416C = 1;
    }
    if (PadIsTriggered_1839f0((void *)&D_004B2570, 0x10) != 0 ||
        PadIsTriggered_1839f0((void *)&D_004B2570, 0x40) != 0 ||
        PadIsTriggered_1839f0((void *)&D_004B2570, 0x80) != 0 ||
        PadIsTriggered_1839f0((void *)&D_004B2570, 0x20) != 0 ||
        PadIsTriggered_1839f0((void *)&D_004B2570, 0x800) != 0) {
        if (D_00481B90 != 0 && D_0048416C != 0 && D_00484198 == 0) {
            ScreenFadeOutColor_1cf730(GetCurrentScene_1f5be0(), 0xA, 0.0f, 0.0f, 0.0f);
            D_00484198 = 1;
        }
    }
    if (D_00484198 < 0xC) {
        if (title_TitleMovieUpdate_4f04c0() != 0) {
            title_TitleMovieRelease_4f0440();
            D_00481B90 = 1;
            D_004803B0 = 1.0f;
            D_004803B4 = D_0047D56C;
            D_00484194 = 0;
            D_00484198 = 0;
            D_00484164 = 0;
            title_TitleMenuWidgetsSetup_4ece80(D_00484160, D_00484170);
            D_0048417C = 1;
            D_00484188 = 0;
            D_0048418C = 0;
            title_TitleMoviePlay_4f0600(title_D_004F1404, D_00484154, 1, D_004803D4);
        } else {
            D_00484164 = D_00484164 + 1;
        }
    }
    if (D_00484198 != 0) {
        m = D_00484198 + 1;
        n = m;
        D_00484198 = m;
        if (n > 0xE) {
            D_0048417C = 1;
            StateMachineSetState_28ede0(D_00484158, 4, 1);
            D_00484198 = 0;
        } else if (n == 0xC) {
            title_TitleMovieStop_4f0480();
            title_TitleMovieRelease_4f0440();
            D_00484164 = 0;
        }
    }
    return 1;
}
