/* rgp:protos */
#define RGP_SELF_normal_HelpMenuShutdown_522eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00522EB0 -- the shop screen's teardown: drops the two overlay
 * archives, releases both cached buffers and zeroes the module's twelve gp
 * state words.  Pass-33 LIST rank: 200 bytes, 50 instructions, TWO conditional
 * branches, 10 calls.
 *
 * D_004B2570 is a MAIN-image address the overlay's splat config leaves as a
 * literal `lui`/`addiu` pair rather than a %hi/%lo relocation; declared as a
 * `const u8` incomplete array it comes back as exactly that pair, and olink
 * derives its value from the symbol NAME.
 *
 * Both releases are guards whose BODY is the fall-through arm.  The `addiu
 * $2,$0,1` that appears in the second guard's branch-likely slot is not a
 * return value -- it is the constant stored into D_004807B4 four instructions
 * later, materialised on both paths. */

extern u8 D_004B2570[];

extern void *D_0048499C;          /* gp - 0x7D4  */
extern void *D_004849A0;          /* gp - 0x7D0  */
extern s16   D_004807B4;          /* gp - 0x49BC */
extern s16   D_004849C0;          /* gp - 0x7B0  */
extern s8    D_004849B8;          /* gp - 0x7B8  */
extern s16   D_004849C4;          /* gp - 0x7AC  */
extern s32   D_004849E8;          /* gp - 0x788  */
extern s32   D_004849EC;          /* gp - 0x784  */
extern s32   D_004849F0;          /* gp - 0x780  */
extern s16   D_004849F4;          /* gp - 0x77C  */
extern s16   D_004849F8;          /* gp - 0x778  */
extern s8    D_004849FC;          /* gp - 0x774  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_HelpMenuShutdown_522eb0(void);

void normal_HelpMenuShutdown_522eb0(void)
{
    void *h;

    normal_InsectEntryMenuFileRelease_524620();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    h = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(h, 0x32D);
    NameTableFreeGroup_158ac0(h, 0x32C);
    if (D_0048499C != 0) {
        MemStackReset_14d830(D_0048499C);
    }
    if (D_004849A0 != 0) {
        MemStackReset_14d830(D_004849A0);
    }
    D_0048499C = 0;
    D_004807B4 = 1;
    D_004849A0 = 0;
    D_004849C0 = 0;
    D_004849B8 = 0;
    D_004849C4 = 0;
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    D_004849E8 = 0;
    D_004849EC = 0;
    D_004849F0 = 0;
    D_004849F4 = 0;
    D_004849F8 = 0;
    D_004849FC = 0;
}
