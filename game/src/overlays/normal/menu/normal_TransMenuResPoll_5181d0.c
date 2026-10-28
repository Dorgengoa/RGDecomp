/* rgp:protos */
#define RGP_SELF_normal_TransMenuResPoll_5181d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005181D0 -- the gameplay scene's menu registration: three state
 * gates on D_00484788, then the 0x526730..0x5267F0 descriptor blocks are
 * handed one at a time to the menu built on func_28B270's handle, the scene
 * widgets are brought up by normal_TransMenuLayoutBuild_516e20, and the gate is armed.
 *
 * FOUR early exits and EVERY one of them materialises its own `daddu $2,$0,$0`
 * in its own delay slot -- so all four are `return 0`, not `break`s into a
 * shared tail (main-pass31 section 1: count the exits).  The last path's
 * `addiu $2,$0,1` is SHARED between the D_00484750 store and the return.
 *
 * `daddu $16,$2,$0` sits in func_206A40's DELAY SLOT and captures
 * func_28B270's result, not func_206A40's.
 * `addiu $5,$0,2 / daddu $6,$5,$0` is mwcc sharing the constant between
 * arguments 2 and 3, not two source constants.
 * The `lw $4,-0x9E8($28)` in each `bnel`'s likely slot is the NEXT block's
 * argument load hoisted into the slot, not part of the guard. */

extern u8 normal_D_00526730[];
extern u8 normal_D_00526748[];
extern u8 normal_D_00526758[];
extern u8 normal_D_00526770[];
extern u8 normal_D_00526790[];
extern u8 normal_D_005267B0[];
extern u8 normal_D_005267D0[];
extern u8 normal_D_005267F0[];

extern void *D_004846E0;          /* gp - 0xA90 */
extern s16   D_00484750;          /* gp - 0xA20 */
extern s32   D_00484770;          /* gp - 0xA00 */
extern s32   D_00484774;          /* gp - 0x9FC */
extern void *D_00484788;          /* gp - 0x9E8 */

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

s32 normal_TransMenuResPoll_5181d0(void)
{
    void *h;
    void *ob;
    void *ctx;
    s32   sel;

    h = D_004846E0;
    if (LoadHandleGetId_28b220(D_00484788) == -1) {
        return 0;
    }
    if (((unsigned char)LoadHandleIsPending_28b210(D_00484788)) == 0) {
        return 0;
    }
    if (LoadHandleGetStatus_28b2e0(D_00484788) == 1) {
        ob = LoadHandleGetData_28b270(D_00484788, &sel);
        ctx = GetMenuResGroup_206a40();
        ResGroupLoadByKind_42b840(ctx, 2, 2, h, ob);
        D_00484770 = MsgTableLoadFromArchive_202a50(ob, normal_D_00526730, h);
        D_00484774 = MsgTableLoadFromArchive_202a50(ob, normal_D_00526748, h);
        ({ __typeof__(ArchiveGetFileByPath_1c2800(ob, normal_D_00526758, &sel)) rgp_ao0 = ArchiveGetFileByPath_1c2800(ob, normal_D_00526758, &sel); SaveMenuMsgTableParse_376b40(h, rgp_ao0, sel); });
        TexGroupLoadFromArchive_202be0(ob, normal_D_00526770, h, 0x32D, 0);
        TexGroupLoadFromArchive_202be0(ob, normal_D_00526790, h, 0x32D, 0);
        TexGroupLoadFromArchive_202be0(ob, normal_D_005267B0, h, 0x32D, 0);
        TexGroupLoadFromArchive_202be0(ob, normal_D_005267D0, h, 0x32D, 0);
        TexGroupLoadFromArchive_202be0(ob, normal_D_005267F0, h, 0x32D, 0);
        normal_TransMenuLayoutBuild_516e20();
        LoadHandleFree_28b230(D_00484788);
        D_00484750 = 1;
        return 1;
    }
    return 0;
}
