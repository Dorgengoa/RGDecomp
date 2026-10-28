/* rgp:protos */
#define RGP_SELF_normal_InsectEntryMenuShutdown_524270 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00524270 -- the shop screen's light teardown: drops both archives
 * and the cached buffer, then resets four gp state cells.  Pass-33 LIST rank:
 * 92 bytes, 23 instructions, ZERO branches, 5 calls.  The heavy twin is
 * normal_FUN_00522EB0, which also frees the two handles. */

extern u8 D_004B2570[];

extern s16 D_004807B4;            /* gp - 0x49BC */
extern s8  D_004849B8;            /* gp - 0x7B8  */
extern s16 D_004849C0;            /* gp - 0x7B0  */
extern s16 D_004849C4;            /* gp - 0x7AC  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_InsectEntryMenuShutdown_524270(void);

void normal_InsectEntryMenuShutdown_524270(void)
{
    normal_InsectEntryMenuFileRelease_524620();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    D_004849C0 = 0;
    D_004807B4 = 1;
    D_004849B8 = 0;
    D_004849C4 = 0;
}
